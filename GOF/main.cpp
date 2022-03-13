#include "GOF.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GOF w(100, 100);
    w.show();
    return a.exec();
}
