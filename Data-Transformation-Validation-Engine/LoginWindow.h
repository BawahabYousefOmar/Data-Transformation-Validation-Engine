#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

// ============================================================
//  LoginWindow

//  Supports two hard-coded roles for the demo:
//    Admin  → username: "admin"  / password: "admin123"
//    Worker → username: "worker" / password: "work123"
//
//  On success MainWindow reads
//  isAdmin() to configure role-gated features.
//

// ============================================================
class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

    // True  → logged-in user has Admin privileges
    // False → Worker 
    bool isAdmin() const;

private slots:
    void onSignInClicked();
    void onInputChanged();          // enables/disables the Sign In button

private:
    Ui::LoginWindow* ui;
    bool m_adminRole = false;

    // Returns true and sets m_adminRole if credentials match
    bool authenticate(const QString& username, const QString& password);

    void showError(const QString& message);
    void clearError();
    void applyStyleSheet();
};