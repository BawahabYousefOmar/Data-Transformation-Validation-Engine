#include <QApplication>
#include <QStyleFactory>
#include "LoginWindow.h"
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setStyle(QStyleFactory::create("Fusion"));

    while (true) {
        LoginWindow login;
        if (login.exec() != QDialog::Accepted)
            break;

        MainWindow* mainWin = new MainWindow(login.isAdmin(), login.username());
        mainWin->setAttribute(Qt::WA_DeleteOnClose);
        mainWin->show();

        QEventLoop loop;
        QObject::connect(mainWin, &QObject::destroyed, &loop, &QEventLoop::quit);
        loop.exec();
    }

    return 0;
}
