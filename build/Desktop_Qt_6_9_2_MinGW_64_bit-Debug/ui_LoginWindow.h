/********************************************************************************
** Form generated from reading UI file 'LoginWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QHBoxLayout *rootLayout;
    QFrame *leftPanel;
    QVBoxLayout *leftLayout;
    QLabel *logoIconLabel;
    QSpacerItem *spacerItem;
    QLabel *heroTitleLabel;
    QSpacerItem *spacerItem1;
    QLabel *heroSubLabel;
    QSpacerItem *spacerItem2;
    QFrame *statChip1;
    QHBoxLayout *hboxLayout;
    QLabel *chip1Icon;
    QLabel *chip1Text;
    QSpacerItem *spacerItem3;
    QFrame *statChip2;
    QHBoxLayout *hboxLayout1;
    QLabel *chip2Icon;
    QLabel *chip2Text;
    QSpacerItem *spacerItem4;
    QFrame *statChip3;
    QHBoxLayout *hboxLayout2;
    QLabel *chip3Icon;
    QLabel *chip3Text;
    QSpacerItem *spacerItem5;
    QLabel *copyrightLabel;
    QFrame *rightPanel;
    QVBoxLayout *rightLayout;
    QLabel *signInHeadingLabel;
    QSpacerItem *spacerItem6;
    QLabel *signInSubLabel;
    QSpacerItem *spacerItem7;
    QLabel *usernameLabel;
    QSpacerItem *spacerItem8;
    QLineEdit *usernameInput;
    QSpacerItem *spacerItem9;
    QLabel *passwordLabel;
    QSpacerItem *spacerItem10;
    QLineEdit *passwordInput;
    QSpacerItem *spacerItem11;
    QLabel *errorLabel;
    QSpacerItem *spacerItem12;
    QPushButton *signInButton;
    QSpacerItem *spacerItem13;
    QLabel *demoHintLabel;
    QSpacerItem *spacerItem14;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(860, 540);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LoginWindow->sizePolicy().hasHeightForWidth());
        LoginWindow->setSizePolicy(sizePolicy);
        rootLayout = new QHBoxLayout(LoginWindow);
        rootLayout->setSpacing(0);
        rootLayout->setObjectName("rootLayout");
        rootLayout->setContentsMargins(0, 0, 0, 0);
        leftPanel = new QFrame(LoginWindow);
        leftPanel->setObjectName("leftPanel");
        leftPanel->setMinimumWidth(340);
        leftPanel->setMaximumWidth(340);
        leftLayout = new QVBoxLayout(leftPanel);
        leftLayout->setSpacing(0);
        leftLayout->setObjectName("leftLayout");
        leftLayout->setContentsMargins(40, 50, 40, 40);
        logoIconLabel = new QLabel(leftPanel);
        logoIconLabel->setObjectName("logoIconLabel");
        logoIconLabel->setAlignment(Qt::AlignLeft);

        leftLayout->addWidget(logoIconLabel);

        spacerItem = new QSpacerItem(20, 60, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(spacerItem);

        heroTitleLabel = new QLabel(leftPanel);
        heroTitleLabel->setObjectName("heroTitleLabel");

        leftLayout->addWidget(heroTitleLabel);

        spacerItem1 = new QSpacerItem(20, 16, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(spacerItem1);

        heroSubLabel = new QLabel(leftPanel);
        heroSubLabel->setObjectName("heroSubLabel");

        leftLayout->addWidget(heroSubLabel);

        spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(spacerItem2);

        statChip1 = new QFrame(leftPanel);
        statChip1->setObjectName("statChip1");
        hboxLayout = new QHBoxLayout(statChip1);
        hboxLayout->setObjectName("hboxLayout");
        hboxLayout->setContentsMargins(12, 8, 12, 8);
        chip1Icon = new QLabel(statChip1);
        chip1Icon->setObjectName("chip1Icon");

        hboxLayout->addWidget(chip1Icon);

        chip1Text = new QLabel(statChip1);
        chip1Text->setObjectName("chip1Text");

        hboxLayout->addWidget(chip1Text);


        leftLayout->addWidget(statChip1);

        spacerItem3 = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(spacerItem3);

        statChip2 = new QFrame(leftPanel);
        statChip2->setObjectName("statChip2");
        hboxLayout1 = new QHBoxLayout(statChip2);
        hboxLayout1->setObjectName("hboxLayout1");
        hboxLayout1->setContentsMargins(12, 8, 12, 8);
        chip2Icon = new QLabel(statChip2);
        chip2Icon->setObjectName("chip2Icon");

        hboxLayout1->addWidget(chip2Icon);

        chip2Text = new QLabel(statChip2);
        chip2Text->setObjectName("chip2Text");

        hboxLayout1->addWidget(chip2Text);


        leftLayout->addWidget(statChip2);

        spacerItem4 = new QSpacerItem(20, 8, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(spacerItem4);

        statChip3 = new QFrame(leftPanel);
        statChip3->setObjectName("statChip3");
        hboxLayout2 = new QHBoxLayout(statChip3);
        hboxLayout2->setObjectName("hboxLayout2");
        hboxLayout2->setContentsMargins(12, 8, 12, 8);
        chip3Icon = new QLabel(statChip3);
        chip3Icon->setObjectName("chip3Icon");

        hboxLayout2->addWidget(chip3Icon);

        chip3Text = new QLabel(statChip3);
        chip3Text->setObjectName("chip3Text");

        hboxLayout2->addWidget(chip3Text);


        leftLayout->addWidget(statChip3);

        spacerItem5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        leftLayout->addItem(spacerItem5);

        copyrightLabel = new QLabel(leftPanel);
        copyrightLabel->setObjectName("copyrightLabel");

        leftLayout->addWidget(copyrightLabel);


        rootLayout->addWidget(leftPanel);

        rightPanel = new QFrame(LoginWindow);
        rightPanel->setObjectName("rightPanel");
        rightLayout = new QVBoxLayout(rightPanel);
        rightLayout->setSpacing(0);
        rightLayout->setObjectName("rightLayout");
        rightLayout->setContentsMargins(56, 80, 56, 56);
        signInHeadingLabel = new QLabel(rightPanel);
        signInHeadingLabel->setObjectName("signInHeadingLabel");

        rightLayout->addWidget(signInHeadingLabel);

        spacerItem6 = new QSpacerItem(20, 6, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem6);

        signInSubLabel = new QLabel(rightPanel);
        signInSubLabel->setObjectName("signInSubLabel");

        rightLayout->addWidget(signInSubLabel);

        spacerItem7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem7);

        usernameLabel = new QLabel(rightPanel);
        usernameLabel->setObjectName("usernameLabel");

        rightLayout->addWidget(usernameLabel);

        spacerItem8 = new QSpacerItem(20, 6, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem8);

        usernameInput = new QLineEdit(rightPanel);
        usernameInput->setObjectName("usernameInput");

        rightLayout->addWidget(usernameInput);

        spacerItem9 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem9);

        passwordLabel = new QLabel(rightPanel);
        passwordLabel->setObjectName("passwordLabel");

        rightLayout->addWidget(passwordLabel);

        spacerItem10 = new QSpacerItem(20, 6, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem10);

        passwordInput = new QLineEdit(rightPanel);
        passwordInput->setObjectName("passwordInput");
        passwordInput->setEchoMode(QLineEdit::Password);

        rightLayout->addWidget(passwordInput);

        spacerItem11 = new QSpacerItem(20, 12, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem11);

        errorLabel = new QLabel(rightPanel);
        errorLabel->setObjectName("errorLabel");
        errorLabel->setVisible(false);

        rightLayout->addWidget(errorLabel);

        spacerItem12 = new QSpacerItem(20, 28, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem12);

        signInButton = new QPushButton(rightPanel);
        signInButton->setObjectName("signInButton");

        rightLayout->addWidget(signInButton);

        spacerItem13 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem13);

        demoHintLabel = new QLabel(rightPanel);
        demoHintLabel->setObjectName("demoHintLabel");
        demoHintLabel->setAlignment(Qt::AlignHCenter);
        demoHintLabel->setWordWrap(true);

        rightLayout->addWidget(demoHintLabel);

        spacerItem14 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        rightLayout->addItem(spacerItem14);


        rootLayout->addWidget(rightPanel);


        retranslateUi(LoginWindow);

        signInButton->setDefault(true);


        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "DataValve \342\200\224 Sign In", nullptr));
        logoIconLabel->setText(QCoreApplication::translate("LoginWindow", "\342\254\241", nullptr));
        heroTitleLabel->setText(QCoreApplication::translate("LoginWindow", "Data<br/>Validation<br/>Engine", nullptr));
        heroSubLabel->setText(QCoreApplication::translate("LoginWindow", "Parse \302\267 Validate \302\267 Export", nullptr));
        chip1Icon->setText(QCoreApplication::translate("LoginWindow", "\342\234\246", nullptr));
        chip1Text->setText(QCoreApplication::translate("LoginWindow", "Multi-file batch processing", nullptr));
        chip2Icon->setText(QCoreApplication::translate("LoginWindow", "\342\234\246", nullptr));
        chip2Text->setText(QCoreApplication::translate("LoginWindow", "Configurable rule engine", nullptr));
        chip3Icon->setText(QCoreApplication::translate("LoginWindow", "\342\234\246", nullptr));
        chip3Text->setText(QCoreApplication::translate("LoginWindow", "Admin & Worker roles", nullptr));
        copyrightLabel->setText(QCoreApplication::translate("LoginWindow", "\302\251 2025 DataValve Team", nullptr));
        signInHeadingLabel->setText(QCoreApplication::translate("LoginWindow", "Welcome back", nullptr));
        signInSubLabel->setText(QCoreApplication::translate("LoginWindow", "Sign in to your account to continue", nullptr));
        usernameLabel->setText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        usernameInput->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        passwordInput->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Enter password", nullptr));
        errorLabel->setText(QString());
        signInButton->setText(QCoreApplication::translate("LoginWindow", "Sign In", nullptr));
        demoHintLabel->setText(QCoreApplication::translate("LoginWindow", "Demo \342\200\224 Admin: admin / admin123 \302\267 Worker: worker / work123", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
