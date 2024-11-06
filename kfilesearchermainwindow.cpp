#include "kfilesearchermainwindow.h"
#include "ui_kfilesearchermainwindow.h"

#include <QDebug>
#include <QQueue>
#include <QFileDialog>
#include <QPushButton>
#include <QWidget>
#include <QStandardPaths>

#include "kfilesaver.h"
#include "kfiledeleter.h"
#include "kkeymonitor.h"
#include "KFileInfos.h"
#include "kfiledetailsmodel.h"

#include "kfileinfos.h"
#include "KmpSearch.h"

#include <QApplication>
#include <QStandardPaths>
#include <QQueue>
#include <QWidget>
#include <QCompleter>
#include <QSettings>
#include <QDebug>


KFileSearcherMainWindow::KFileSearcherMainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::KFileSearcherMainWindow),
        m_isRegExpEnable(false)
{
    ui->setupUi(this);

//下列代码用来实现搜索框的索引
    QString exePath=QCoreApplication::applicationDirPath();
    QString iniFile=exePath+"/local.ini";
    m_IniFile = new QSettings(iniFile, QSettings::IniFormat,this);
    QString searchName =m_IniFile->value("client/searchName").toString();
    m_searchNameList=searchName.split("|");
    ui->comboBox_2->setEditable(true);
    ui->comboBox_2->setCurrentText(m_searchNameList.at(0));
    ui->comboBox_2->addItems(m_searchNameList);

    //下列两行是实现索引的自动补全
    QCompleter *completer = new QCompleter(m_searchNameList);
    ui->comboBox->setCompleter(completer);
//
    connect(ui->m_inputLineEdit, &QLineEdit::textEdited,
            this, &KFileSearcherMainWindow::onFilterChanged, Qt::QueuedConnection);
    connect(ui->m_filter_ComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &KFileSearcherMainWindow::onFilterChanged, Qt::QueuedConnection);
    connect(ui->m_detailsView->model(), &KFileDetailsModel::dataChanged, this, [&]() {
        ui->m_statusbar->showMessage(QString(tr("%1个对象")).arg(ui->m_detailsView->model()->rowCount()));
    });
    ui->m_statusbar->showMessage(QString(tr("%1个对象")).arg(ui->m_detailsView->model()->rowCount()));

    // 绑定信号，实现快捷键隐藏和显示
    connect(KKeyMonitor::instance(), &KKeyMonitor::hideShortcutPressed,
            this, &KFileSearcherMainWindow::on_m_hideAction_triggered);
}

KFileSearcherMainWindow::~KFileSearcherMainWindow()
{
    delete ui;
}
//内容匹配字符串改变


void KFileSearcherMainWindow::onFilterChanged()
{
    KFileFilter filter;
    filter.setPattern(ui->m_inputLineEdit->text());
    filter.setIsRegExpEnabled(m_isRegExpEnable);
    switch (ui->m_filter_ComboBox->currentIndex()) {
    case 0:
        filter.setFilterType(KFileFilter::None);
        break;
    case 1:
        filter.setFilterType(KFileFilter::Dir);
        break;
    case 2:
        filter.setFilterType(KFileFilter::File);
        break;
    default:
        break;
    }
    ui->m_detailsView->model()->installFilter(filter);
}

void KFileSearcherMainWindow::on_m_regExpAction_triggered(bool checked)
{
    m_isRegExpEnable = checked;
    onFilterChanged();
}

void KFileSearcherMainWindow::on_m_quitAction_triggered()
{
    close();
}

void KFileSearcherMainWindow::on_m_exportAction_triggered()
{
    if (ui->m_detailsView->selectedIndexes().isEmpty())
    {
        QMessageBox::critical(this, tr("失败"), tr("请先左键选中再导出（按住Ctrl可以选择多个）"));
        return;
    }
    QString destPath = QFileDialog::getExistingDirectory(this);
    KFileSaver saver(ui->m_detailsView->model()->fileInfos(ui->m_detailsView->selectedIndexes()), destPath, this);
}

void KFileSearcherMainWindow::on_m_selectAllAction_triggered()
{
    ui->m_detailsView->selectAll();
}

void KFileSearcherMainWindow::on_m_deleteAction_triggered()
{
    if (ui->m_detailsView->selectedIndexes().isEmpty())
    {
        QMessageBox::critical(this, tr("失败"), tr("请先左键选中再删除（按住Ctrl可以选择多个）"));
        return;
    }
    KFileDeleter deleter(ui->m_detailsView->model()->fileInfos(ui->m_detailsView->selectedIndexes()), this);
}

void KFileSearcherMainWindow::on_m_hideAction_triggered()
{
    if (isHidden())
        show();
    else
        hide();
}

QString targetDirectory;

//这个是指定目的文件夹按钮的函数
void KFileSearcherMainWindow::on_toolButton_clicked()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("save path"),QDir::currentPath()));

    if(!directory.isEmpty())
    {
        if(ui->comboBox->findText(directory)==-1)
        {
            ui->comboBox->addItem(directory);
        }
        ui->comboBox->setCurrentIndex(ui->comboBox->findText(directory));
        targetDirectory = ui->comboBox->currentText();
    }
}



//开始搜索按钮的函数
void KFileSearcherMainWindow::on_startSearchButton_clicked()
{
    QString currentContent=ui->comboBox_2->currentText();
    if(m_searchNameList.contains(currentContent)){
        m_searchNameList.removeAt(ui->comboBox_2->currentIndex());
    }
    m_searchNameList.push_front(currentContent);
    m_searchNameList.removeAll("");
    QString searchName;
    for (int i=0;i<m_searchNameList.size();i++ ) {
        if(i==m_searchNameList.size()-1){
            searchName+=m_searchNameList.at(i);
        }else{
            searchName+=m_searchNameList.at(i)+"|";
        }
    }
    m_IniFile->setValue("client/searchName",searchName);

    //
    KFileFilter filter;
    filter.setPattern(currentContent);
    filter.setIsRegExpEnabled(m_isRegExpEnable);
    ui->m_detailsView->model()->pat = currentContent.toStdString();
    //
}



KFileInfos *KFileInfos::s_fileInfos = nullptr;


KFileInfos::KFileInfos(QObject *parent) :
    QObject{parent}
{
    updateFileInfos();
    m_timer.setInterval(1000);
    connect(&m_timer, &QTimer::timeout,this, &KFileInfos::updateFileInfos, Qt::QueuedConnection);
    m_timer.start();
}

KFileInfos::~KFileInfos()
{
    //m_timer.stop();
}

const KFileInfos *KFileInfos::instance()
{
    if (!s_fileInfos)
        s_fileInfos = new KFileInfos(qApp);  // 设置parent为qApp，加入Qt对象生命周期管理
    return s_fileInfos;
}

const QFileInfoList &KFileInfos::fileInfoList() const
{
    return m_fileInfoList;
}

void KFileInfos::updateFileInfos()
{
    QDir sourceDir = QDir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    if(targetDirectory=="")sourceDir = QDir(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));
    else sourceDir = targetDirectory;


    QFileInfoList fileInfos;
    QFileInfoList totalFileInfos;

    QQueue<QDir> queue;
    queue.push_back(sourceDir);

    // 广度优先搜索遍历全部文件
    while (!queue.empty())
    {
        sourceDir = queue.dequeue();
        fileInfos = sourceDir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);
        foreach (const QFileInfo &fileInfo, fileInfos){
            if (fileInfo.isDir()){
                queue.push_back(QDir(fileInfo.absoluteFilePath()));
                //totalFileInfos.append(fileInfo);
            }
            if(fileInfo.suffix()=="txt"||fileInfo.suffix()=="docx"||fileInfo.suffix()=="doc"||fileInfo.suffix()=="pdf"/*||fileInfo.isDir()*/){
                totalFileInfos.append(fileInfo);
            }
        }
    }
    if (totalFileInfos == m_fileInfoList)
        return;

    m_fileInfoList = totalFileInfos;
    emit filesChanged();
}

int KFileDetailsModel::searchIndex = 1;

void KFileSearcherMainWindow::on_pushButton_2_clicked()
{
    KFileDetailsModel::searchIndex++;
}


void KFileSearcherMainWindow::on_pushButton_clicked()
{
    KFileDetailsModel::searchIndex--;
    if(KFileDetailsModel::searchIndex < 1)KFileDetailsModel::searchIndex = 1 ;
}

