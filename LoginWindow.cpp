#include "LoginWindow.h"
#include "ui_LoginWindow.h"

LoginWindow::LoginWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Frameless fixed-size window
    setFixedSize(860, 540);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    applyStyleSheet();

    ui->signInButton->setEnabled(false);

    connect(ui->signInButton,  &QPushButton::clicked,
            this, &LoginWindow::onSignInClicked);
    connect(ui->usernameInput, &QLineEdit::textChanged,
            this, &LoginWindow::onInputChanged);
    connect(ui->passwordInput, &QLineEdit::textChanged,
            this, &LoginWindow::onInputChanged);
    connect(ui->passwordInput, &QLineEdit::returnPressed,
            this, &LoginWindow::onSignInClicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

bool LoginWindow::isAdmin() const
{
    return m_adminRole;
}

void LoginWindow::onSignInClicked()
{
    QString user = ui->usernameInput->text().trimmed();
    QString pass = ui->passwordInput->text();

    if (authenticate(user, pass)) {
        clearError();
        accept();
    } else {
        showError("Invalid username or password. Please try again.");
        ui->passwordInput->clear();
        ui->passwordInput->setFocus();
    }
}

void LoginWindow::onInputChanged()
{
    bool ready = !ui->usernameInput->text().trimmed().isEmpty()
              && !ui->passwordInput->text().isEmpty();
    ui->signInButton->setEnabled(ready);
    clearError();
}

bool LoginWindow::authenticate(const QString& username, const QString& password)
{
    if (username == "admin" && password == "admin123") {
        m_adminRole = true;
        return true;
    }
    if (username == "worker" && password == "work123") {
        m_adminRole = false;
        return true;
    }
    return false;
}

void LoginWindow::showError(const QString& message)
{
    ui->errorLabel->setText(message);
    ui->errorLabel->setVisible(true);
}

void LoginWindow::clearError()
{
    ui->errorLabel->clear();
    ui->errorLabel->setVisible(false);
}

void LoginWindow::applyStyleSheet()
{
    setStyleSheet(R"(
        /* Dialog */
        QDialog {
            background: palette(window);
            border-radius: 0px;
        }

        /* Left branding panel */
        QFrame#leftPanel {
            background-color: #0D1117;
            border-right: 1px solid #1E2A35;
        }

        QLabel#logoIconLabel {
            font-size: 28px;
            color: #00BCD4;
            font-family: monospace;
        }

        QLabel#heroTitleLabel {
            font-size: 36px;
            font-weight: 900;
            color: #FFFFFF;
            line-height: 1.1;
            letter-spacing: -1px;
            font-family: "Segoe UI", sans-serif;
        }

        QLabel#heroSubLabel {
            font-size: 11px;
            color: #00BCD4;
            letter-spacing: 4px;
            font-family: "Courier New", monospace;
            text-transform: uppercase;
        }

        /* Feature chips */
        QFrame#statChip1, QFrame#statChip2, QFrame#statChip3 {
            background-color: rgba(0, 188, 212, 0.08);
            border: 1px solid rgba(0, 188, 212, 0.25);
            border-radius: 6px;
        }

        QFrame#statChip1 QLabel, QFrame#statChip2 QLabel, QFrame#statChip3 QLabel {
            color: #8BA5B8;
            font-size: 11px;
        }

        QFrame#statChip1 QLabel[objectName="chip1Icon"],
        QFrame#statChip2 QLabel[objectName="chip2Icon"],
        QFrame#statChip3 QLabel[objectName="chip3Icon"] {
            color: #00BCD4;
            font-size: 10px;
            padding-right: 6px;
        }

        QLabel#copyrightLabel {
            color: #3D5060;
            font-size: 10px;
        }

        /* Sign-in form */
        QFrame#rightPanel {
            background: palette(window);
        }

        QLabel#signInHeadingLabel {
            font-size: 28px;
            font-weight: 700;
            color: palette(text);
            font-family: "Segoe UI", sans-serif;
        }

        QLabel#signInSubLabel {
            font-size: 13px;
            color: palette(mid);
        }

        QLabel#usernameLabel, QLabel#passwordLabel {
            font-size: 12px;
            font-weight: 600;
            color: palette(text);
            letter-spacing: 0.3px;
        }

        QLineEdit#usernameInput, QLineEdit#passwordInput {
            border: 1.5px solid palette(mid);
            border-radius: 8px;
            padding: 10px 14px;
            font-size: 13px;
            background: palette(base);
            color: palette(text);
            min-height: 20px;
        }

        QLineEdit#usernameInput:focus, QLineEdit#passwordInput:focus {
            border-color: #00BCD4;
            background: palette(base);
        }

        QLabel#errorLabel {
            font-size: 12px;
            color: #EF5350;
            background-color: rgba(239, 83, 80, 0.08);
            border: 1px solid rgba(239, 83, 80, 0.3);
            border-radius: 6px;
            padding: 8px 12px;
        }

        QPushButton#signInButton {
            background-color: #00BCD4;
            color: #000000;
            border: none;
            border-radius: 8px;
            padding: 12px 0;
            font-size: 14px;
            font-weight: 700;
            letter-spacing: 0.5px;
        }

        QPushButton#signInButton:hover {
            background-color: #26C6DA;
        }

        QPushButton#signInButton:pressed {
            background-color: #0097A7;
        }

        QPushButton#signInButton:disabled {
            background-color: palette(mid);
            color: palette(dark);
        }

        QLabel#demoHintLabel {
            font-size: 10px;
            color: palette(mid);
            font-family: "Courier New", monospace;
        }
    )");
}
