/********************************************************************************
** Form generated from reading UI file 'kfilesearchermainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KFILESEARCHERMAINWINDOW_H
#define UI_KFILESEARCHERMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "kfiledetailsview.h"

QT_BEGIN_NAMESPACE

class Ui_KFileSearcherMainWindow
{
public:
    QAction *m_quitAction;
    QAction *m_exportAction;
    QAction *m_selectAllAction;
    QAction *m_regExpAction;
    QAction *m_deleteAction;
    QAction *m_hideAction;
    QWidget *m_centralwidget;
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QLabel *label;
    QComboBox *comboBox_2;
    QHBoxLayout *horizontalLayout;
    QLineEdit *m_inputLineEdit;
    QComboBox *m_filter_ComboBox;
    QToolButton *toolButton;
    QPushButton *startSearchButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton;
    KFileDetailsView *m_detailsView;
    QMenuBar *m_menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *m_statusbar;

    void setupUi(QMainWindow *KFileSearcherMainWindow)
    {
        if (KFileSearcherMainWindow->objectName().isEmpty())
            KFileSearcherMainWindow->setObjectName("KFileSearcherMainWindow");
        KFileSearcherMainWindow->resize(932, 703);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(KFileSearcherMainWindow->sizePolicy().hasHeightForWidth());
        KFileSearcherMainWindow->setSizePolicy(sizePolicy);
        QFont font;
        font.setPointSize(9);
        KFileSearcherMainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/new/prefix1/a00wj-ge2av.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        KFileSearcherMainWindow->setWindowIcon(icon);
        m_quitAction = new QAction(KFileSearcherMainWindow);
        m_quitAction->setObjectName("m_quitAction");
        m_exportAction = new QAction(KFileSearcherMainWindow);
        m_exportAction->setObjectName("m_exportAction");
        m_selectAllAction = new QAction(KFileSearcherMainWindow);
        m_selectAllAction->setObjectName("m_selectAllAction");
        m_regExpAction = new QAction(KFileSearcherMainWindow);
        m_regExpAction->setObjectName("m_regExpAction");
        m_regExpAction->setCheckable(true);
        m_deleteAction = new QAction(KFileSearcherMainWindow);
        m_deleteAction->setObjectName("m_deleteAction");
        m_hideAction = new QAction(KFileSearcherMainWindow);
        m_hideAction->setObjectName("m_hideAction");
        m_centralwidget = new QWidget(KFileSearcherMainWindow);
        m_centralwidget->setObjectName("m_centralwidget");
        gridLayout = new QGridLayout(m_centralwidget);
        gridLayout->setObjectName("gridLayout");
        comboBox = new QComboBox(m_centralwidget);
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(100);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy1);
        comboBox->setMinimumSize(QSize(810, 0));
        comboBox->setMaximumSize(QSize(16777215, 16777215));
        comboBox->setEditable(true);

        gridLayout->addWidget(comboBox, 1, 0, 1, 2);

        label = new QLabel(m_centralwidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        comboBox_2 = new QComboBox(m_centralwidget);
        comboBox_2->setObjectName("comboBox_2");
        comboBox_2->setEditable(true);

        gridLayout->addWidget(comboBox_2, 3, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        m_inputLineEdit = new QLineEdit(m_centralwidget);
        m_inputLineEdit->setObjectName("m_inputLineEdit");
        m_inputLineEdit->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(m_inputLineEdit);

        m_filter_ComboBox = new QComboBox(m_centralwidget);
        m_filter_ComboBox->addItem(QString());
        m_filter_ComboBox->addItem(QString());
        m_filter_ComboBox->addItem(QString());
        m_filter_ComboBox->setObjectName("m_filter_ComboBox");

        horizontalLayout->addWidget(m_filter_ComboBox);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 3);

        toolButton = new QToolButton(m_centralwidget);
        toolButton->setObjectName("toolButton");
        toolButton->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(toolButton, 1, 2, 1, 1);

        startSearchButton = new QPushButton(m_centralwidget);
        startSearchButton->setObjectName("startSearchButton");

        gridLayout->addWidget(startSearchButton, 3, 2, 1, 1);

        pushButton_2 = new QPushButton(m_centralwidget);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout->addWidget(pushButton_2, 5, 2, 1, 1);

        pushButton = new QPushButton(m_centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        pushButton->setMaximumSize(QSize(93, 16777215));

        gridLayout->addWidget(pushButton, 5, 0, 1, 1);

        m_detailsView = new KFileDetailsView(m_centralwidget);
        m_detailsView->setObjectName("m_detailsView");

        gridLayout->addWidget(m_detailsView, 4, 0, 1, 3);

        KFileSearcherMainWindow->setCentralWidget(m_centralwidget);
        m_menubar = new QMenuBar(KFileSearcherMainWindow);
        m_menubar->setObjectName("m_menubar");
        m_menubar->setGeometry(QRect(0, 0, 932, 25));
        m_menubar->setFont(font);
        menu = new QMenu(m_menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(m_menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(m_menubar);
        menu_3->setObjectName("menu_3");
        KFileSearcherMainWindow->setMenuBar(m_menubar);
        m_statusbar = new QStatusBar(KFileSearcherMainWindow);
        m_statusbar->setObjectName("m_statusbar");
        KFileSearcherMainWindow->setStatusBar(m_statusbar);

        m_menubar->addAction(menu->menuAction());
        m_menubar->addAction(menu_2->menuAction());
        m_menubar->addAction(menu_3->menuAction());
        menu->addAction(m_exportAction);
        menu->addAction(m_hideAction);
        menu->addAction(m_quitAction);
        menu_2->addAction(m_selectAllAction);
        menu_2->addAction(m_deleteAction);
        menu_3->addAction(m_regExpAction);

        retranslateUi(KFileSearcherMainWindow);

        QMetaObject::connectSlotsByName(KFileSearcherMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *KFileSearcherMainWindow)
    {
        KFileSearcherMainWindow->setWindowTitle(QCoreApplication::translate("KFileSearcherMainWindow", "\346\226\207\344\273\266\345\205\250\346\226\207\346\220\234\347\264\242\345\267\245\345\205\267\345\272\223", nullptr));
        m_quitAction->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\351\200\200\345\207\272", nullptr));
#if QT_CONFIG(shortcut)
        m_quitAction->setShortcut(QCoreApplication::translate("KFileSearcherMainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        m_exportAction->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\345\260\206\351\200\211\344\270\255\347\232\204\346\226\207\344\273\266\345\257\274\345\207\272\345\210\260", nullptr));
#if QT_CONFIG(shortcut)
        m_exportAction->setShortcut(QCoreApplication::translate("KFileSearcherMainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        m_selectAllAction->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\345\205\250\351\200\211", nullptr));
#if QT_CONFIG(shortcut)
        m_selectAllAction->setShortcut(QCoreApplication::translate("KFileSearcherMainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        m_regExpAction->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\344\275\277\347\224\250\346\255\243\345\210\231\350\241\250\350\276\276\345\274\217", nullptr));
#if QT_CONFIG(shortcut)
        m_regExpAction->setShortcut(QCoreApplication::translate("KFileSearcherMainWindow", "Ctrl+R", nullptr));
#endif // QT_CONFIG(shortcut)
        m_deleteAction->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255\346\226\207\344\273\266", nullptr));
#if QT_CONFIG(shortcut)
        m_deleteAction->setShortcut(QCoreApplication::translate("KFileSearcherMainWindow", "Del", nullptr));
#endif // QT_CONFIG(shortcut)
        m_hideAction->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\351\232\220\350\227\217/\346\230\276\347\244\272", nullptr));
#if QT_CONFIG(shortcut)
        m_hideAction->setShortcut(QCoreApplication::translate("KFileSearcherMainWindow", "Alt+Space", nullptr));
#endif // QT_CONFIG(shortcut)
        label->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\351\200\211\346\213\251\347\233\256\346\240\207\346\226\207\344\273\266\345\244\271", nullptr));
        comboBox_2->setCurrentText(QString());
        m_inputLineEdit->setPlaceholderText(QCoreApplication::translate("KFileSearcherMainWindow", "\350\257\267\350\276\223\345\205\245\346\226\207\344\273\266\345\220\215\357\274\210\346\224\257\346\214\201\346\213\274\351\237\263\346\220\234\347\264\242\357\274\211", nullptr));
        m_filter_ComboBox->setItemText(0, QCoreApplication::translate("KFileSearcherMainWindow", "\346\211\200\346\234\211", nullptr));
        m_filter_ComboBox->setItemText(1, QCoreApplication::translate("KFileSearcherMainWindow", "\346\226\207\344\273\266\345\244\271", nullptr));
        m_filter_ComboBox->setItemText(2, QCoreApplication::translate("KFileSearcherMainWindow", "\346\226\207\344\273\266", nullptr));

        toolButton->setText(QCoreApplication::translate("KFileSearcherMainWindow", "...", nullptr));
        startSearchButton->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\345\274\200\345\247\213\346\220\234\347\264\242", nullptr));
        pushButton_2->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\345\220\216\344\270\200\344\270\252\346\220\234\347\264\242", nullptr));
        pushButton->setText(QCoreApplication::translate("KFileSearcherMainWindow", "\345\211\215\344\270\200\344\270\252\346\220\234\347\264\242", nullptr));
        menu->setTitle(QCoreApplication::translate("KFileSearcherMainWindow", "\346\226\207\344\273\266", nullptr));
        menu_2->setTitle(QCoreApplication::translate("KFileSearcherMainWindow", "\347\274\226\350\276\221", nullptr));
        menu_3->setTitle(QCoreApplication::translate("KFileSearcherMainWindow", "\346\220\234\347\264\242", nullptr));
    } // retranslateUi

};

namespace Ui {
    class KFileSearcherMainWindow: public Ui_KFileSearcherMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KFILESEARCHERMAINWINDOW_H
