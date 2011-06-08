#ifndef MAPVIEWCONTROLLER_H
#define MAPVIEWCONTROLLER_H

#include <vector>
#include "QuadTree.hpp"

class LadyBug;
class Location;
class Region;
class MainWindow;
class MapView;
class MapViewController
{
public:
    MapViewController();
    ~MapViewController();
    void showRegion(Region region);

private:
    QuadTree<Location> *tree;
    MapView *mapView;
    MainWindow *mainWindow;
    std::vector<LadyBug *> *ladybugs;
};

#endif // MAPVIEWCONTROLLER_H
