#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication qapp(argc, argv);
    MainWindow hwnd;
    hwnd.show();
    return qapp.exec();
}
