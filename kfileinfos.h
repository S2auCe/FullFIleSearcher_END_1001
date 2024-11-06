#ifndef KFILEINFOS_H
#define KFILEINFOS_H

#include <QFileInfo>
#include <QTimer>
#include <Qdir>
#include <QWidget>
#include <string>

#include "kfilesearchermainwindow.h"
#include "ui_kfilesearchermainwindow.h"

static Ui::KFileSearcherMainWindow *ui = nullptr;

/**
 * @brief KFileInfos类缓存了桌面全部文件和文件夹的信息，采用单例模式，全局唯一。构造时创建定时器，每隔1s刷新一次信息，以便于同步桌面文件的变化。
 */
class KFileInfos : public QObject
{
    Q_OBJECT
public:

    explicit KFileInfos(QObject *parent = nullptr);
    /**
     * @brief 返回实例对象，采用懒汉单例模式，如果未初始化则自动初始化
     * @return
     */
    static const KFileInfos *instance();

    /**
     * @brief fileInfoList
     * @return
     */
    const QFileInfoList &fileInfoList() const;

    void updateFileInfos();

private:


    ~KFileInfos();

    /**
     * @brief 单例模式的静态变量
     */
    static KFileInfos *s_fileInfos;

    /**
     * @brief 文件信息列表
     */
    QFileInfoList m_fileInfoList;

    /**
     * @brief 文件内容简略
     */
    std::vector<std::string> fileBrief;

    /**
     * @brief 计时器每两秒发送一次信号，更新文件信息
     */
    QTimer m_timer;

    /**
     * @brief 自动更新文件信息的函数
     */


signals:
    void filesChanged();
};

#endif // KFILEINFOS_H
