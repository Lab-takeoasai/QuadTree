#include <QtGui/QApplication>

#include "mapviewcontroller.h"


#include <string>
#include <vector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MapViewController *controller = new MapViewController();

    return a.exec();
}
