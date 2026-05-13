/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *centralLayout;
    QFrame *sidebar;
    QVBoxLayout *sidebarLayout;
    QFrame *sidebarBrandFrame;
    QHBoxLayout *hboxLayout;
    QLabel *sidebarLogoLabel;
    QLabel *sidebarAppNameLabel;
    QSpacerItem *spacerItem;
    QFrame *userBadgeFrame;
    QHBoxLayout *hboxLayout1;
    QLabel *userAvatarLabel;
    QVBoxLayout *vboxLayout;
    QLabel *userNameLabel;
    QLabel *userRoleLabel;
    QFrame *sidebarDivider1;
    QLabel *sectionMainLabel;
    QPushButton *navUploadBtn;
    QPushButton *navReportsBtn;
    QFrame *sidebarDivider2;
    QLabel *sectionAdminLabel;
    QPushButton *navStandardsBtn;
    QSpacerItem *spacerItem1;
    QPushButton *logoutButton;
    QVBoxLayout *contentAreaLayout;
    QFrame *topBar;
    QHBoxLayout *topBarLayout;
    QLabel *pageHeadingLabel;
    QSpacerItem *spacerItem2;
    QLabel *statusIndicatorLabel;
    QStackedWidget *pageStack;
    QWidget *pageUpload;
    QVBoxLayout *pageUploadLayout;
    QLabel *uploadPlaceholderLabel;
    QWidget *pageReports;
    QVBoxLayout *pageReportsLayout;
    QLabel *reportsPlaceholderLabel;
    QWidget *pageStandards;
    QVBoxLayout *pageStandardsLayout;
    QLabel *standardsPlaceholderLabel;
    QFrame *statusBar;
    QHBoxLayout *statusBarLayout;
    QLabel *statusBarLabel;
    QSpacerItem *spacerItem3;
    QLabel *versionLabel;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1280, 800);
        MainWindow->setMinimumSize(QSize(1024, 680));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        centralLayout = new QHBoxLayout(centralWidget);
        centralLayout->setSpacing(0);
        centralLayout->setObjectName("centralLayout");
        centralLayout->setContentsMargins(0, 0, 0, 0);
        sidebar = new QFrame(centralWidget);
        sidebar->setObjectName("sidebar");
        sidebar->setMinimumWidth(220);
        sidebar->setMaximumWidth(220);
        sidebarLayout = new QVBoxLayout(sidebar);
        sidebarLayout->setSpacing(4);
        sidebarLayout->setObjectName("sidebarLayout");
        sidebarLayout->setContentsMargins(12, 20, 12, 16);
        sidebarBrandFrame = new QFrame(sidebar);
        sidebarBrandFrame->setObjectName("sidebarBrandFrame");
        hboxLayout = new QHBoxLayout(sidebarBrandFrame);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(8, 0, -1, 0);
        sidebarLogoLabel = new QLabel(sidebarBrandFrame);
        sidebarLogoLabel->setObjectName("sidebarLogoLabel");

        hboxLayout->addWidget(sidebarLogoLabel);

        sidebarAppNameLabel = new QLabel(sidebarBrandFrame);
        sidebarAppNameLabel->setObjectName("sidebarAppNameLabel");

        hboxLayout->addWidget(sidebarAppNameLabel);

        spacerItem = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        hboxLayout->addItem(spacerItem);


        sidebarLayout->addWidget(sidebarBrandFrame);

        userBadgeFrame = new QFrame(sidebar);
        userBadgeFrame->setObjectName("userBadgeFrame");
        hboxLayout1 = new QHBoxLayout(userBadgeFrame);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(8, 6, 8, 6);
        userAvatarLabel = new QLabel(userBadgeFrame);
        userAvatarLabel->setObjectName("userAvatarLabel");

        hboxLayout1->addWidget(userAvatarLabel);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setSpacing(0);
        vboxLayout->setObjectName("vboxLayout");
        userNameLabel = new QLabel(userBadgeFrame);
        userNameLabel->setObjectName("userNameLabel");

        vboxLayout->addWidget(userNameLabel);

        userRoleLabel = new QLabel(userBadgeFrame);
        userRoleLabel->setObjectName("userRoleLabel");

        vboxLayout->addWidget(userRoleLabel);


        hboxLayout1->addLayout(vboxLayout);


        sidebarLayout->addWidget(userBadgeFrame);

        sidebarDivider1 = new QFrame(sidebar);
        sidebarDivider1->setObjectName("sidebarDivider1");
        sidebarDivider1->setFrameShape(QFrame::HLine);
        sidebarDivider1->setFrameShadow(QFrame::Plain);

        sidebarLayout->addWidget(sidebarDivider1);

        sectionMainLabel = new QLabel(sidebar);
        sectionMainLabel->setObjectName("sectionMainLabel");

        sidebarLayout->addWidget(sectionMainLabel);

        navUploadBtn = new QPushButton(sidebar);
        navUploadBtn->setObjectName("navUploadBtn");
        navUploadBtn->setCheckable(true);
        navUploadBtn->setFlat(true);

        sidebarLayout->addWidget(navUploadBtn);

        navReportsBtn = new QPushButton(sidebar);
        navReportsBtn->setObjectName("navReportsBtn");
        navReportsBtn->setCheckable(true);
        navReportsBtn->setFlat(true);

        sidebarLayout->addWidget(navReportsBtn);

        sidebarDivider2 = new QFrame(sidebar);
        sidebarDivider2->setObjectName("sidebarDivider2");
        sidebarDivider2->setFrameShape(QFrame::HLine);
        sidebarDivider2->setFrameShadow(QFrame::Plain);

        sidebarLayout->addWidget(sidebarDivider2);

        sectionAdminLabel = new QLabel(sidebar);
        sectionAdminLabel->setObjectName("sectionAdminLabel");

        sidebarLayout->addWidget(sectionAdminLabel);

        navStandardsBtn = new QPushButton(sidebar);
        navStandardsBtn->setObjectName("navStandardsBtn");
        navStandardsBtn->setCheckable(true);
        navStandardsBtn->setFlat(true);

        sidebarLayout->addWidget(navStandardsBtn);

        spacerItem1 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        sidebarLayout->addItem(spacerItem1);

        logoutButton = new QPushButton(sidebar);
        logoutButton->setObjectName("logoutButton");
        logoutButton->setFlat(true);

        sidebarLayout->addWidget(logoutButton);


        centralLayout->addWidget(sidebar);

        contentAreaLayout = new QVBoxLayout();
        contentAreaLayout->setSpacing(0);
        contentAreaLayout->setObjectName("contentAreaLayout");
        contentAreaLayout->setContentsMargins(0, 0, 0, 0);
        topBar = new QFrame(centralWidget);
        topBar->setObjectName("topBar");
        topBar->setMaximumHeight(52);
        topBarLayout = new QHBoxLayout(topBar);
        topBarLayout->setObjectName("topBarLayout");
        topBarLayout->setContentsMargins(24, 0, 24, 0);
        pageHeadingLabel = new QLabel(topBar);
        pageHeadingLabel->setObjectName("pageHeadingLabel");

        topBarLayout->addWidget(pageHeadingLabel);

        spacerItem2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        topBarLayout->addItem(spacerItem2);

        statusIndicatorLabel = new QLabel(topBar);
        statusIndicatorLabel->setObjectName("statusIndicatorLabel");

        topBarLayout->addWidget(statusIndicatorLabel);


        contentAreaLayout->addWidget(topBar);

        pageStack = new QStackedWidget(centralWidget);
        pageStack->setObjectName("pageStack");
        pageUpload = new QWidget();
        pageUpload->setObjectName("pageUpload");
        pageUploadLayout = new QVBoxLayout(pageUpload);
        pageUploadLayout->setObjectName("pageUploadLayout");
        pageUploadLayout->setContentsMargins(24, 24, 24, 24);
        uploadPlaceholderLabel = new QLabel(pageUpload);
        uploadPlaceholderLabel->setObjectName("uploadPlaceholderLabel");
        uploadPlaceholderLabel->setAlignment(Qt::AlignCenter);

        pageUploadLayout->addWidget(uploadPlaceholderLabel);

        pageStack->addWidget(pageUpload);
        pageReports = new QWidget();
        pageReports->setObjectName("pageReports");
        pageReportsLayout = new QVBoxLayout(pageReports);
        pageReportsLayout->setObjectName("pageReportsLayout");
        pageReportsLayout->setContentsMargins(24, 24, 24, 24);
        reportsPlaceholderLabel = new QLabel(pageReports);
        reportsPlaceholderLabel->setObjectName("reportsPlaceholderLabel");
        reportsPlaceholderLabel->setAlignment(Qt::AlignCenter);

        pageReportsLayout->addWidget(reportsPlaceholderLabel);

        pageStack->addWidget(pageReports);
        pageStandards = new QWidget();
        pageStandards->setObjectName("pageStandards");
        pageStandardsLayout = new QVBoxLayout(pageStandards);
        pageStandardsLayout->setObjectName("pageStandardsLayout");
        pageStandardsLayout->setContentsMargins(24, 24, 24, 24);
        standardsPlaceholderLabel = new QLabel(pageStandards);
        standardsPlaceholderLabel->setObjectName("standardsPlaceholderLabel");
        standardsPlaceholderLabel->setAlignment(Qt::AlignCenter);

        pageStandardsLayout->addWidget(standardsPlaceholderLabel);

        pageStack->addWidget(pageStandards);

        contentAreaLayout->addWidget(pageStack);

        statusBar = new QFrame(centralWidget);
        statusBar->setObjectName("statusBar");
        statusBar->setMaximumHeight(28);
        statusBarLayout = new QHBoxLayout(statusBar);
        statusBarLayout->setObjectName("statusBarLayout");
        statusBarLayout->setContentsMargins(16, 0, 16, 0);
        statusBarLabel = new QLabel(statusBar);
        statusBarLabel->setObjectName("statusBarLabel");

        statusBarLayout->addWidget(statusBarLabel);

        spacerItem3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        statusBarLayout->addItem(spacerItem3);

        versionLabel = new QLabel(statusBar);
        versionLabel->setObjectName("versionLabel");

        statusBarLayout->addWidget(versionLabel);


        contentAreaLayout->addWidget(statusBar);


        centralLayout->addLayout(contentAreaLayout);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "DataValve \342\200\224 Data Validation Engine", nullptr));
        sidebarLogoLabel->setText(QCoreApplication::translate("MainWindow", "\342\254\241", nullptr));
        sidebarAppNameLabel->setText(QCoreApplication::translate("MainWindow", "DataValve", nullptr));
        userAvatarLabel->setText(QCoreApplication::translate("MainWindow", "\360\237\221\244", nullptr));
        userNameLabel->setText(QCoreApplication::translate("MainWindow", "\342\200\224", nullptr));
        userRoleLabel->setText(QCoreApplication::translate("MainWindow", "\342\200\224", nullptr));
        sectionMainLabel->setText(QCoreApplication::translate("MainWindow", "MAIN", nullptr));
        navUploadBtn->setText(QCoreApplication::translate("MainWindow", "  Upload & Validate", nullptr));
        navReportsBtn->setText(QCoreApplication::translate("MainWindow", "  Reports", nullptr));
        sectionAdminLabel->setText(QCoreApplication::translate("MainWindow", "ADMIN", nullptr));
        navStandardsBtn->setText(QCoreApplication::translate("MainWindow", "  Standards Manager", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "Sign Out", nullptr));
        pageHeadingLabel->setText(QCoreApplication::translate("MainWindow", "Upload & Validate", nullptr));
        statusIndicatorLabel->setText(QCoreApplication::translate("MainWindow", "\342\227\217 Ready", nullptr));
        uploadPlaceholderLabel->setText(QCoreApplication::translate("MainWindow", "Upload widget loads here", nullptr));
        reportsPlaceholderLabel->setText(QCoreApplication::translate("MainWindow", "Reports table loads here", nullptr));
        standardsPlaceholderLabel->setText(QCoreApplication::translate("MainWindow", "Standards manager loads here", nullptr));
        statusBarLabel->setText(QCoreApplication::translate("MainWindow", "Ready", nullptr));
        versionLabel->setText(QCoreApplication::translate("MainWindow", "v1.0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
