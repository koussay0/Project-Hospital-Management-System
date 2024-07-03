#include "login.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    logIn w;
    w.show();
    return a.exec();
}
