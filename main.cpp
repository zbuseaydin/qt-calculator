#include "hw.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Hw w;
    w.show();
    return a.exec();
}
