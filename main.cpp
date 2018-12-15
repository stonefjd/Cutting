#include "windowcutting.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WindowCutting w;
    w.show();

    return a.exec();
}
