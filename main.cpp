#include <QApplication>
#include <QStyleFactory>
#include <QString> 
#include "LoginWindow.h"
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    while (true) {
        LoginWindow login;


        if (login.exec() != QDialog::Accepted) {
            break;
        }

        // Retrieve the admin status from your LoginWindow
        bool isAdmin = login.isAdmin();



        QString displayName = isAdmin ? "Admin User" : "Data Worker";

        // Dynamically create the MainWindow
        MainWindow* mainWin = new MainWindow(isAdmin, displayName);
        mainWin->setAttribute(Qt::WA_DeleteOnClose);
        mainWin->show();

        QEventLoop loop;
        QObject::connect(mainWin, &QObject::destroyed, &loop, &QEventLoop::quit);
        loop.exec();
    }

    return 0;
}
