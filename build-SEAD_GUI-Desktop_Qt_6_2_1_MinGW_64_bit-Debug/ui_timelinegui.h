/********************************************************************************
** Form generated from reading UI file 'timelinegui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TIMELINEGUI_H
#define UI_TIMELINEGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TimelineGUI
{
public:
    QWidget *centralwidget;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *mainHorizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TimelineGUI)
    {
        if (TimelineGUI->objectName().isEmpty())
            TimelineGUI->setObjectName(QString::fromUtf8("TimelineGUI"));
        TimelineGUI->resize(800, 600);
        centralwidget = new QWidget(TimelineGUI);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(80, 100, 391, 171));
        mainHorizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        mainHorizontalLayout->setObjectName(QString::fromUtf8("mainHorizontalLayout"));
        mainHorizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        radioButton = new QRadioButton(horizontalLayoutWidget);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setEnabled(false);

        verticalLayout_2->addWidget(radioButton);

        radioButton_2 = new QRadioButton(horizontalLayoutWidget);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));

        verticalLayout_2->addWidget(radioButton_2);


        mainHorizontalLayout->addLayout(verticalLayout_2);

        TimelineGUI->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TimelineGUI);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        TimelineGUI->setMenuBar(menubar);
        statusbar = new QStatusBar(TimelineGUI);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        TimelineGUI->setStatusBar(statusbar);

        retranslateUi(TimelineGUI);

        QMetaObject::connectSlotsByName(TimelineGUI);
    } // setupUi

    void retranslateUi(QMainWindow *TimelineGUI)
    {
        TimelineGUI->setWindowTitle(QCoreApplication::translate("TimelineGUI", "TimelineGUI", nullptr));
        radioButton->setText(QCoreApplication::translate("TimelineGUI", "Standard", nullptr));
        radioButton_2->setText(QCoreApplication::translate("TimelineGUI", "Non-Standard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TimelineGUI: public Ui_TimelineGUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TIMELINEGUI_H
