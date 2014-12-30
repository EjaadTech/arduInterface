#include "arduinterface.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    arduinterface w;
    w.show();

    return a.exec();
}
