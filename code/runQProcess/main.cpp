#include <QtGui/QApplication>
#include "tesqprocess.h"
#include <iostream>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <cstdlib>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    tesQProcess w;
    w.show();
    return a.exec();
}
