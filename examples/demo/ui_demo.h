/********************************************************************************
** Form generated from reading UI file 'demo.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "QPageIndicator"
#include "QSwipeView"

QT_BEGIN_NAMESPACE

class Ui_demo
{
public:
    QVBoxLayout *verticalLayout;
    QSwipeView *stackedWidget;
    QWidget *page_1;
    QHBoxLayout *horizontalLayout_2;
    QWidget *p1_container;
    QLabel *p1_title;
    QLabel *p1_desc;
    QWidget *page_3;
    QWidget *p2_container;
    QLabel *p2_title;
    QTabWidget *tabWidget;
    QWidget *tab;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QComboBox *comboBox;
    QWidget *tab_2;
    QWidget *page_5;
    QWidget *p4_container;
    QLabel *p4_title;
    QLabel *p4_desc;
    QHBoxLayout *horizontalLayout;
    QToolButton *prev;
    QSpacerItem *horizontalSpacerL;
    QPageIndicator *pageIndicator;
    QSpacerItem *horizontalSpacerR;
    QToolButton *next;

    void setupUi(QDialog *demo)
    {
        if (demo->objectName().isEmpty())
            demo->setObjectName(QString::fromUtf8("demo"));
        demo->resize(480, 286);
        verticalLayout = new QVBoxLayout(demo);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        stackedWidget = new QSwipeView(demo);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        page_1 = new QWidget();
        page_1->setObjectName(QString::fromUtf8("page_1"));
        horizontalLayout_2 = new QHBoxLayout(page_1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        p1_container = new QWidget(page_1);
        p1_container->setObjectName(QString::fromUtf8("p1_container"));
        p1_title = new QLabel(p1_container);
        p1_title->setObjectName(QString::fromUtf8("p1_title"));
        p1_title->setGeometry(QRect(10, 10, 171, 61));
        p1_title->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
"font-weight: bold;"));
        p1_desc = new QLabel(p1_container);
        p1_desc->setObjectName(QString::fromUtf8("p1_desc"));
        p1_desc->setGeometry(QRect(10, 70, 431, 151));
        p1_desc->setStyleSheet(QString::fromUtf8("font-size: 14px;"));
        p1_desc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        p1_desc->setWordWrap(true);

        horizontalLayout_2->addWidget(p1_container);

        stackedWidget->addWidget(page_1);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        p2_container = new QWidget(page_3);
        p2_container->setObjectName(QString::fromUtf8("p2_container"));
        p2_container->setGeometry(QRect(0, 0, 445, 230));
        p2_title = new QLabel(p2_container);
        p2_title->setObjectName(QString::fromUtf8("p2_title"));
        p2_title->setGeometry(QRect(10, 10, 301, 61));
        p2_title->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
"font-weight: bold;\n"
""));
        tabWidget = new QTabWidget(p2_container);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 70, 431, 131));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        radioButton = new QRadioButton(tab);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(10, 10, 121, 21));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(tab);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(10, 40, 131, 21));
        comboBox = new QComboBox(tab);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 70, 141, 23));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        stackedWidget->addWidget(page_3);
        page_5 = new QWidget();
        page_5->setObjectName(QString::fromUtf8("page_5"));
        p4_container = new QWidget(page_5);
        p4_container->setObjectName(QString::fromUtf8("p4_container"));
        p4_container->setGeometry(QRect(0, 0, 445, 230));
        p4_title = new QLabel(p4_container);
        p4_title->setObjectName(QString::fromUtf8("p4_title"));
        p4_title->setGeometry(QRect(10, 10, 271, 61));
        p4_title->setStyleSheet(QString::fromUtf8("font-size: 24px;\n"
"font-weight: bold;"));
        p4_desc = new QLabel(p4_container);
        p4_desc->setObjectName(QString::fromUtf8("p4_desc"));
        p4_desc->setGeometry(QRect(10, 70, 431, 141));
        p4_desc->setStyleSheet(QString::fromUtf8("font-size: 14px;"));
        p4_desc->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        p4_desc->setWordWrap(true);
        stackedWidget->addWidget(page_5);

        verticalLayout->addWidget(stackedWidget);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        prev = new QToolButton(demo);
        prev->setObjectName(QString::fromUtf8("prev"));
        prev->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("arrow-left");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        prev->setIcon(icon);
        prev->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout->addWidget(prev);

        horizontalSpacerL = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacerL);

        pageIndicator = new QPageIndicator(demo);
        pageIndicator->setObjectName(QString::fromUtf8("pageIndicator"));
        pageIndicator->setPageCount(3);

        horizontalLayout->addWidget(pageIndicator);

        horizontalSpacerR = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacerR);

        next = new QToolButton(demo);
        next->setObjectName(QString::fromUtf8("next"));
        next->setStyleSheet(QString::fromUtf8(""));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("arrow-right");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8("."), QSize(), QIcon::Normal, QIcon::Off);
        }
        next->setIcon(icon1);
        next->setToolButtonStyle(Qt::ToolButtonIconOnly);

        horizontalLayout->addWidget(next);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(demo);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(demo);
    } // setupUi

    void retranslateUi(QDialog *demo)
    {
        demo->setWindowTitle(QCoreApplication::translate("demo", "Dialog", nullptr));
        p1_title->setText(QCoreApplication::translate("demo", "Welcome!", nullptr));
        p1_desc->setText(QCoreApplication::translate("demo", "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.", nullptr));
        p2_title->setText(QCoreApplication::translate("demo", "Widgets", nullptr));
        radioButton->setText(QCoreApplication::translate("demo", "Radio Button", nullptr));
        radioButton_2->setText(QCoreApplication::translate("demo", "Radio Button 2", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("demo", "Item 1", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("demo", "Item 2", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("demo", "Item 3", nullptr));

        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("demo", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("demo", "Tab 2", nullptr));
        p4_title->setText(QCoreApplication::translate("demo", "Last page", nullptr));
        p4_desc->setText(QCoreApplication::translate("demo", "Est ridiculus Class consectetuer leo nullam. Convallis porta condimentum dapibus. Suspendisse aliquam ligula elementum blandit. Massa sit. Tempor nonummy commodo odio id, bibendum.\n"
"\n"
"Consequat, cras suspendisse molestie, cras purus integer tristique quam est lorem.", nullptr));
        prev->setText(QCoreApplication::translate("demo", "Prev", nullptr));
        next->setText(QCoreApplication::translate("demo", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class demo: public Ui_demo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEMO_H
