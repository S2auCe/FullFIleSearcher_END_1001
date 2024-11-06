#include <QApplication>

#include "kfilesearchermainwindow.h"

int main(int argc, char *argv[])
{
    //QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication a(argc, argv);
    KFileSearcherMainWindow w;
    QMessageBox messageBox(QMessageBox::NoIcon, QObject::tr("文件全文搜索功能库"),
                           QObject::tr("启动后默认隐藏，按Alt+空格唤出。"), QMessageBox::Ok, &w);
    messageBox.exec();
    return a.exec();
}
