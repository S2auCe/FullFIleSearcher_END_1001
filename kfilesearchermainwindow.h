#ifndef KFILESEARCHER_KFILESEARCHERMAINWINDOW_H
#define KFILESEARCHER_KFILESEARCHERMAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QWidget>
#include <QSettings>

#include "kfilesavethread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class KFileSearcherMainWindow; }
QT_END_NAMESPACE

/**
 * @brief 文件搜索器的主窗口类
 */
class KFileSearcherMainWindow : public QMainWindow
{
Q_OBJECT

public:

    explicit KFileSearcherMainWindow(QWidget *parent = nullptr);

    ~KFileSearcherMainWindow() override;

    Ui::KFileSearcherMainWindow *ui;

    //QString targetDirectory;
private slots:
    void on_m_regExpAction_triggered(bool checked);

    void on_m_quitAction_triggered();

    void on_m_exportAction_triggered();

    void on_m_selectAllAction_triggered();

    void on_m_deleteAction_triggered();

    void on_m_hideAction_triggered();

    void on_toolButton_clicked();
    //选择文件路径按钮

    void on_startSearchButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:


    bool m_isRegExpEnable;

    /**
     * @brief 当过滤条件变化时，触发此函数
     */
    void onFilterChanged();

    QSettings *m_IniFile;
    QStringList m_searchNameList;

};


#endif //KFILESEARCHER_KFILESEARCHERMAINWINDOW_H
