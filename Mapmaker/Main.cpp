#include <QtGui/QApplication>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QLCDNumber>
#include <QtGui/QFont>
#include <QtGui/QVBoxLayout>
#include "mainwdiget.h"

int main(int argc,char * argv[])
{
    QApplication app(argc,argv);

    mainwdiget w;
    w.show();

    return app.exec();
}
