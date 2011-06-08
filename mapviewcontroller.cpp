#include "mapviewcontroller.h"

#include "mapview.h"
#include "mainwindow.h"


#include <QPixmap>
#include <vector>
#include "imageview.h"



#include "region.hpp"
#include "location.hpp"
#include "ladybug.hpp"

MapViewController::MapViewController() {

    Region region = Region(50, 50, 1000, 1000);   //  Regionは全体

    //  create ladybugs
    this->tree = new QuadTree<Location>(region);
    this->ladybugs = new std::vector<LadyBug *>();
    for(;;) {
        LadyBug *ladybug = new LadyBug("", "/Users/asai/Desktop/gps.txt");
        std::vector<Location *> locs = ladybug->getLocations();
        for ( unsigned int i = 0; i < locs.size(); i++ ) {
            if ( !locs.at(i)->isError )
                  this->tree->add(locs.at(i));
        }
        this->ladybugs->push_back(ladybug);
        break;  //  TODO: add many ladybugs
    }

    //  create MainWindow
    this->mainWindow = new MainWindow();


    //  create MapView
    QPixmap *image = new QPixmap();
    image->load("/Users/takeo/Desktop/image.jpg");
    this->mapView = new MapView(this->mainWindow);
    this->mapView->setGeometry(0,0,this->mainWindow->width(), this->mainWindow->height());
    this->mapView->setImage(image);
    this->mapView->setViewController(this);
    this->mapView->setRegion(&region);


    this->mainWindow->show();
}

MapViewController::~MapViewController() {
    delete this->mainWindow;
    delete this->tree;
}


void MapViewController::showRegion(Region region) {
    //  TODO: regionから、treeを検索し、適切なimageをpopupする
    printf("----get here!\n");

    QPixmap *image = new QPixmap();
    image->load("/Users/takeo/Desktop/image.jpg");


    //
    Location *loc = this->tree->findFirstObjectInRegion(region);
    if ( loc != NULL ) {
        //printf("found (%f, %f)", loc->x, loc->y);
    } else {
        printf("not found");
    }


    ImageView *imageView = new ImageView();
    imageView->setImage(image);
    imageView->show();


}
