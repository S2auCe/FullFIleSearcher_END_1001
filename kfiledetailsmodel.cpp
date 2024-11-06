#include "kfiledetailsmodel.h"
#include "ui_kfilesearchermainwindow.h"

#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
#include <algorithm>
#include <cmath>
#include <QFileIconProvider>

#include "kfileinfos.h"
#include "kpinyin.h"
#include "KmpSearch.h"
#include "KmpSearch2.h"

QVector<QVector<int>> KFileDetailsModel::s_LCSArray;

KFileDetailsModel::KFileDetailsModel(QObject *parent) :
    QAbstractTableModel(parent),
    m_currentPage(0),        // 初始化当前页为0
    m_itemsPerPage(100)       // 默认每页100个条目
{
    m_headerList << tr("名称") << tr("路径") << tr("大小") << tr("修改时间") << tr("内容");
    m_fileInfos = KFileInfos::instance()->fileInfoList();

    connect(KFileInfos::instance(), &KFileInfos::filesChanged, this, [&]() {
        installFilter(m_fileFilter);
    }, Qt::QueuedConnection);

}

QVariant KFileDetailsModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section >= 0 && section < m_headerList.size()) {
            return m_headerList[section];
        }
    }
    return QAbstractTableModel::headerData(section, orientation, role);
}


int KFileDetailsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return currentPageFileInfos().size(); // 返回当前页的数据行数

}

int KFileDetailsModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return m_headerList.size();
}

QVariant KFileDetailsModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role == Qt::DisplayRole) {
        const QFileInfoList currentFileInfos = currentPageFileInfos(); // 获取当前页的文件信息

        if (index.column() >= 0 && index.column() < m_headerList.size() &&
            index.row() >= 0 && index.row() < currentFileInfos.size()) {
            switch (index.column()) {
                case 0:
                    return currentFileInfos[index.row()].fileName();
                case 1:
                    return currentFileInfos[index.row()].absoluteFilePath();
                case 2:
                    return currentFileInfos[index.row()].isFile() ?
                           QString("%1KB").arg(currentFileInfos[index.row()].size() / 1024) :
                           QString();
                case 3:
                    return currentFileInfos[index.row()].lastModified().toString("yyyy-MM-dd hh:mm:ss");
                case 4: // 新添加的列
                    return readFileContent(currentFileInfos[index.row()].absoluteFilePath());
                default:
                    break;
            }
        }
    } else if (role == Qt::DecorationRole) {
        if (index.column() == 0)
            return QFileIconProvider().icon(currentPageFileInfos()[index.row()]);
    }
    return QVariant();
}

void KFileDetailsModel::sort(int column, Qt::SortOrder order)
{
    m_columnSortedBy = column;
    m_orderSortedBy = order;

    // 根据不同的列选择不同的排序函数
    std::function<bool(const QFileInfo &, const QFileInfo &)> compareFunction;
    switch (column) {
    case 0:
        compareFunction = [&](const QFileInfo &_a, const QFileInfo &_b)
        {
            if (order == Qt::AscendingOrder)
                return _a.fileName() < _b.fileName();
            else
                return _a.fileName() > _b.fileName();
        };
        break;
    case 1:
        compareFunction = [&](const QFileInfo &_a, const QFileInfo &_b)
        {
            if (order == Qt::AscendingOrder)
                return _a.absoluteFilePath() < _b.absoluteFilePath();
            else
                return _a.absoluteFilePath() > _b.absoluteFilePath();
        };
        break;
    case 2:
        compareFunction = [&](const QFileInfo &_a, const QFileInfo &_b)
        {
            if (order == Qt::AscendingOrder)
                return _a.size() < _b.size();
            else
                return _a.size() > _b.size();
        };
        break;
    case 3:
        compareFunction = [&](const QFileInfo &_a, const QFileInfo &_b)
        {
            if (order == Qt::AscendingOrder)
                return _a.lastModified() < _b.lastModified();
            else
                return _a.lastModified() > _b.lastModified();
        };
        break;
    default:
        break;
    }
    std::sort(m_fileInfos.begin(), m_fileInfos.end(), compareFunction);
    emit dataChanged(index(0, 0), index(m_fileInfos.count() - 1, m_headerList.count() - 1));
}

void KFileDetailsModel::installFilter(const KFileFilter &filter)
{
    m_fileFilter = filter;

    // 支持正则表达式的情况，采用 QRegularExpression 匹配
    if (filter.isRegExpEnabled())
    {
        m_fileInfos.clear();
        QRegularExpression regExp(filter.pattern(), QRegularExpression::CaseInsensitiveOption);
        foreach(const QFileInfo &fileInfo, KFileInfos::instance()->fileInfoList())
        {
            // 过滤掉目录
            if (filter.filterType() == KFileFilter::File && fileInfo.isDir())
                continue;
            else if (filter.filterType() == KFileFilter::Dir && fileInfo.isFile())
                continue;

            // 检查文件扩展名以确定文件类型
            QString fileExtension = fileInfo.suffix().toLower();
            if (fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png" ||
                fileExtension == "gif" || fileExtension == "bmp" ||
                fileExtension == "mp3" || fileExtension == "wav" ||
                fileExtension == "mp4" || fileExtension == "avi" ||
                fileExtension == "mkv" || fileExtension == "wmv")
            {
                // 不显示文件内容
                m_fileInfos.append(fileInfo);
                continue; // 仅显示文件名
            }

            QRegularExpressionMatch matchAnswer = regExp.match(fileInfo.fileName());
            if (matchAnswer.hasMatch())
                m_fileInfos.append(fileInfo);
        }
    }
    // 不支持正则表达式的情况，采用 LCS 算法匹配
    else
    {
        m_fileInfos.clear();
        foreach(const QFileInfo &fileInfo, KFileInfos::instance()->fileInfoList())
        {
            // 过滤掉目录
            if (filter.filterType() == KFileFilter::File && fileInfo.isDir())
                continue;
            else if (filter.filterType() == KFileFilter::Dir && fileInfo.isFile())
                continue;

            // 检查文件扩展名以确定文件类型
            QString fileExtension = fileInfo.suffix().toLower();
            if (fileExtension == "jpg" || fileExtension == "jpeg" || fileExtension == "png" ||
                fileExtension == "gif" || fileExtension == "bmp" ||
                fileExtension == "mp3" || fileExtension == "wav" ||
                fileExtension == "mp4" || fileExtension == "avi" ||
                fileExtension == "mkv" || fileExtension == "wmv")
            {
                // 不显示文件内容
                m_fileInfos.append(fileInfo);
                continue; // 仅显示文件名
            }

            if (LCS(filter.pattern(), fileInfo.fileName()) == filter.pattern().length())
            {
                m_fileInfos.append(fileInfo);
                continue;
            }
            QString convertToPinyin, fileName = fileInfo.fileName();
            for (int i = 0; i < fileName.length(); i++)
            {
                ushort uni = fileName[i].unicode();
                if (uni >= 0x4e00 && uni <= 0x9fa5)
                    convertToPinyin += KPinyin::getNoRepeatPingyinForWord(QString(fileName[i]));
                else
                    convertToPinyin += fileName[i];
            }
            if (LCS(filter.pattern(), convertToPinyin) == filter.pattern().length())
                m_fileInfos.append(fileInfo);
        }
    }

    // 读取支持的文本文件内容（Word, TXT, MD）
    foreach (const QFileInfo &fileInfo, m_fileInfos)
    {
        QString fileExtension = fileInfo.suffix().toLower();
        if (fileExtension == "txt" || fileExtension == "md" ||
            fileExtension == "doc" || fileExtension == "docx")
        {
            QFile file(fileInfo.filePath());

            if (file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QTextStream in(&file);
                QString content = in.read(255);  // 读取前255个字符
                file.close();

                // 这里可以存储读取的内容，或者用于进一步处理
                // 例如，将内容与文件信息结合以供显示
            }
        }
    }

    sort(m_columnSortedBy, m_orderSortedBy);
}

QFileInfoList KFileDetailsModel::currentPageFileInfos() const {
    int start = m_currentPage * m_itemsPerPage;
    int end = std::min(start + m_itemsPerPage, (int)m_fileInfos.size());

    QFileInfoList pageFileInfos;
    for (int i = start; i < end; ++i) {
        pageFileInfos.append(m_fileInfos[i]);
    }
    return pageFileInfos;
}

void KFileDetailsModel::setItemsPerPage(int itemsPerPage) {
    m_itemsPerPage = itemsPerPage;
    emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
}

void KFileDetailsModel::setCurrentPage(int page) {
    if (page >= 0 && page < totalPages()) {
        m_currentPage = page;
        emit dataChanged(index(0, 0), index(rowCount() - 1, columnCount() - 1));
    }
}

int KFileDetailsModel::currentPage() const {
    return m_currentPage;
}

int KFileDetailsModel::totalPages() const {
    return (m_fileInfos.size() + m_itemsPerPage - 1) / m_itemsPerPage; // 向上取整
}

QFileInfoList KFileDetailsModel::fileInfos(const QModelIndexList &indexes)
{
    QFileInfoList result;
    foreach(const QModelIndex &index, indexes) {
        if (index.column() == 0)
            result.append(currentPageFileInfos()[index.row()]); // 返回当前页的文件信息
    }
    return result;
}

int KFileDetailsModel::LCS(const QString &a, const QString &b)
{
    if (s_LCSArray.size() < a.length() + 1)
        s_LCSArray.resize(a.length() + 1);
    if (s_LCSArray[0].size() < b.length() + 1)
        s_LCSArray[0].resize(b.length() + 1);
    s_LCSArray[0][0] = 0;
    for (int i = 1; i <= a.length(); i++)
    {
        if (s_LCSArray[i].size() < b.length() + 1)
            s_LCSArray[i].resize(b.length() + 1);
        for (int j = 1; j <= b.length(); j++)
        {
            if (QString::compare(a[i - 1], b[j - 1], Qt::CaseInsensitive) == 0)
                s_LCSArray[i][j] = s_LCSArray[i - 1][j - 1] + 1;
            else
                s_LCSArray[i][j] = std::max(s_LCSArray[i - 1][j], s_LCSArray[i][j - 1]);
        }
    }
    return s_LCSArray[a.length()][b.length()];
}


QString toPinyin(QString Qtxt){
    QString convertToPinyin;
    for (int i = 0; i < Qtxt.length(); i++)
    {

        ushort uni = Qtxt[i].unicode();
        if (uni >= 0x4e00 && uni <= 0x9fa5)
            convertToPinyin += KPinyin::getNoRepeatPingyinForWord(QString(Qtxt[i]));
        else
            convertToPinyin += Qtxt[i];
    }
    return convertToPinyin;
}

int min(int a,int b)
{
    if(a<=b)return a;
    else return b;
}

std::string pat = "";

QString KFileDetailsModel::readFileContent(const QString &filePath) const
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString txt = in.readAll();
        QByteArray content ;// kmp匹配具体内容
//combobox2的内容传入pat里面

        QString Stxt(txt);
        QString Qpat = QString::fromStdString(pat);
        //第一次搜索
        std::vector<int> pos = kmpSearch(Stxt,Qpat);
        qDebug()<< pos;

        QString brief="";

        //当前是显示哪个搜索内容
        int currentIndex = KFileDetailsModel::searchIndex % pos.size();



        if(pos.size() == 1)//若第一次搜索没搜到，则尝试拼音搜索
        {
            brief = "";

            QString convertToPinyin2 = toPinyin(Stxt);
            QString pat2 = toPinyin(Qpat);
            //后缀为2的都为转为拼音后的内容
            pos = kmpSearch(convertToPinyin2 ,pat2);

            if(pos.size() != 1){//搜到了
                currentIndex = KFileDetailsModel::searchIndex % pos.size();
                brief = Stxt.mid(std::max(pos[currentIndex]-30,0),60);
                brief = "...." + brief + "....";
            }else
                return "";
        }else brief = "...." + Stxt.mid(std::max(pos[currentIndex]-30,0),60) + "....";


        return brief;// 返回UTF-8编码的字符串
    }
    return QString(); // 如果无法打开文件，返回空字符串
}
