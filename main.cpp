#include "mymenu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mymenu w;
    w.show();
    return a.exec();
}
