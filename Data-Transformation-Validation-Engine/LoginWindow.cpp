#include "LoginWindow.h"
#include "ui_LoginWindow.h"

#include "UserManager.h"

// ----------------------------------------------------------------
// Constructor
// ----------------------------------------------------------------
LoginWindow::LoginWindow(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Fixed size — no resize handles on the login screen
    setFixedSize(860, 540);
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);

    m_userManager.loadUsers("users.txt");

    applyStyleSheet();

    // Sign In starts disabled until both fields have text
    ui->signInButton->setEnabled(false);

    connect(ui->toggleModeButton, &QPushButton::clicked, this, &LoginWindow::onToggleModeClicked);

    connect(ui->signInButton, &QPushButton::clicked,
        this, &LoginWindow::onSignInClicked);
    connect(ui->usernameInput, &QLineEdit::textChanged,
        this, &LoginWindow::onInputChanged);
    connect(ui->passwordInput, &QLineEdit::textChanged,
        this, &LoginWindow::onInputChanged);
    connect(ui->passwordInput, &QLineEdit::returnPressed,
        this, &LoginWindow::onSignInClicked);
}

// ----------------------------------------------------------------
// Destructor
// ----------------------------------------------------------------
LoginWindow::~LoginWindow()
{
    delete ui;
}

// ----------------------------------------------------------------
// Public API
// ----------------------------------------------------------------
bool LoginWindow::isAdmin() const
{
    return m_adminRole;
}

// ----------------------------------------------------------------
// Private Slots
// ----------------------------------------------------------------
void LoginWindow::onSignInClicked()
{
    string stdUser = ui->usernameInput->text().toStdString();
    string stdPass = ui->passwordInput->text().toStdString();

    if (m_isSignUpMode) {
        // --- SIGN UP ---
        if (m_userManager.registerUser(stdUser, stdPass)) {
            ui->passwordInput->clear();
            onToggleModeClicked(); // Switch back to login mode automatically
        }
        else {
            showError("Username already exists!");
        }
    }
    else {
        // --- LOGIN ---
        if (m_userManager.authenticate(stdUser, stdPass, m_adminRole)) {
            accept(); // Success! Close window
        }
        else {
            showError("Invalid username or password.");
        }
    }
}

void LoginWindow::onInputChanged()
{
    bool ready = !ui->usernameInput->text().trimmed().isEmpty()
        && !ui->passwordInput->text().isEmpty();
    ui->signInButton->setEnabled(ready);
    clearError();
}

void LoginWindow::onToggleModeClicked()
{
    m_isSignUpMode = !m_isSignUpMode;

    if (m_isSignUpMode) {
        ui->signInButton->setText("Sign Up");
        ui->toggleModeButton->setText("Already have an account? Sign In");
    }
    else {
        ui->signInButton->setText("Sign In");
        ui->toggleModeButton->setText("Don't have an account? Sign Up");
    }

    clearError();
}

// ----------------------------------------------------------------
// Private Helpers
// ----------------------------------------------------------------
bool LoginWindow::authenticate(const QString& username, const QString& password)
{
    std::string stdUser = username.toStdString();
    std::string stdPass = password.toStdString();

    return m_userManager.authenticate(stdUser, stdPass, m_adminRole);
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
        /* ── Root dialog ── */
        QDialog {
            background: palette(window);
            border-radius: 0px;
        }

        /* ── LEFT PANEL ── */
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

        /* decorative feature chips */
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

        /* ── RIGHT PANEL ── */
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

        QPushButton#toggleModeButton {
            background-color: transparent;
            color: #00BCD4;
            border: 2px solid #00BCD4;
            border-radius: 8px;
            padding: 10px 0;
            font-size: 14px;
            font-weight: 700;
            letter-spacing: 0.5px;
        }
        QPushButton#toggleModeButton:hover {
            background-color: rgba(0, 188, 212, 0.1);
            color: #26C6DA;
            border-color: #26C6DA;
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