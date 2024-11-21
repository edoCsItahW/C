#include "fivestroke.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FiveStroke w;
    w.setWindowTitle("五笔字根练习");
    w.resize(800, 600);

    w.show();
    return a.exec();
}
