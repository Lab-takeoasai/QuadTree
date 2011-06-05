#include "mapviewcontroller.h"

#include "mapview.h"
#include "mainwindow.h"
#include "region.hpp"

#include <QPixmap>
#include "imageview.h"

MapViewController::MapViewController() {
    this->mainWindow = new MainWindow();

    QPixmap *image = new QPixmap();
    image->load("/Users/takeo/Desktop/image.jpg");

    this->mapView = new MapView(this->mainWindow);
    this->mapView->setGeometry(0,0,this->mainWindow->width(), this->mainWindow->height());
    this->mapView->setImage(image);
    this->mapView->setViewController(this);

    this->mainWindow->show();
}

MapViewController::~MapViewController() {
    delete this->mainWindow;
}


void MapViewController::showRegion(Region region) {
    //  TODO: regionから、treeを検索し、適切なimageをpopupする
    printf("----get here!\n");

    QPixmap *image = new QPixmap();
    image->load("/Users/takeo/Desktop/image.jpg");


    ImageView *imageView = new ImageView();
    imageView->setImage(image);
    imageView->show();


}
