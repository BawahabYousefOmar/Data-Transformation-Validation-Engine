#include "LoginWindow.h"
#include "ui_LoginWindow.h"

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

    applyStyleSheet();

    // Sign In starts disabled until both fields have text
    ui->signInButton->setEnabled(false);

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
    QString user = ui->usernameInput->text().trimmed();
    QString pass = ui->passwordInput->text();

    if (authenticate(user, pass)) {
        clearError();
        accept();
    }
    else {
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

// ----------------------------------------------------------------
// Private Helpers
// ----------------------------------------------------------------
bool LoginWindow::authenticate(const QString& username, const QString& password)
{
    // Admin role
    if (username == "admin" && password == "admin123") {
        m_adminRole = true;
        return true;
    }
    // Worker role
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