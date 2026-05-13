#pragma once

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginWindow; }
QT_END_NAMESPACE

// Sign-in dialog shown before the main window. Demo accounts: admin / admin123, worker / work123.
class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget* parent = nullptr);
    ~LoginWindow();

    // true = admin (full access), false = worker
    bool isAdmin() const;
    QString username() const;

private slots:
    void onSignInClicked();
    void onInputChanged();

private:
    Ui::LoginWindow* ui;
    bool m_adminRole = false;
    QString m_username;

    bool authenticate(const QString& username, const QString& password);

    void showError(const QString& message);
    void clearError();
    void applyStyleSheet();
};
