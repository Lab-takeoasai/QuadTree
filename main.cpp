#include <QtGui/QApplication>

#include "mapviewcontroller.h"


#include <string>
#include <vector>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MapViewController *controller = new MapViewController();

/*
    LadyBug *ladybug = new LadyBug("", "/Users/asai/Desktop/gps.txt");
    QuadTree<Location> *tree = new QuadTree<Location>(Region(50,50,1000,1000));
    std::vector<Location *> locs = ladybug->getLocations();
    for ( unsigned int i = 0; i < locs.size(); i++ ) {
       // if ( !locs.at(i)->isError )
              tree->add(locs.at(i));
    }
    tree->dump();
    //delete ladybug;
*/
    return a.exec();
}
