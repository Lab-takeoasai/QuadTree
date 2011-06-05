#ifndef MAPVIEWCONTROLLER_H
#define MAPVIEWCONTROLLER_H

#include <vector>

class LadyBug;
class Region;
class QuadTree;
class MainWindow;
class MapView;
class MapViewController
{
public:
    MapViewController();
    ~MapViewController();
    void showRegion(Region region);

private:
    QuadTree *tree;
    MapView *mapView;
    MainWindow *mainWindow;
    std::vector<LadyBug> *ladybugs;
};

#endif // MAPVIEWCONTROLLER_H
