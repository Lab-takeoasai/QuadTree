#include "mapview.h"

#include "stdio.h"

#include "imageview.h"
#include "region.hpp"
#include "mapviewcontroller.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent)
{
    this->setImage(NULL);
    this->setRegion(NULL);
}

void MapView::setImage(QPixmap *image) {
    if ( image != NULL ) {
        delete image_;
        image_ = new QPixmap(*image);
    } else {
        image_ = NULL;
    }
}

QPixmap *MapView::getImage() {
    return image_;
}

MapView::~MapView() {
    if ( this->getImage() )
        delete image_;
    if ( this->getRegion() )
        delete region_;
}


void MapView::setRegion(Region *reg) {
    if ( reg != NULL ) {
        this->region_ = new Region(*reg);
    } else {
        this->region_ = NULL;
    }
}

Region *MapView::getRegion() {
    return this->region_;
}

void MapView::setViewController(MapViewController *controller) {
    this->viewController = controller;
}

MapViewController *MapView::getViewController() {
    return this->viewController;
}



//  privates

void MapView::paintEvent(QPaintEvent *e) {
    if ( this->getImage() != NULL ) {
        QPainter painter(this);
        painter.drawPixmap(0,0,*(this->getImage()));
    }
}

void MapView::mousePressEvent(QMouseEvent *) {
    //  TODO: Regionの計算
    //  MapViewのRegionとMouseEventの座標から、検索領域のRegionを作り、Controllerに返す。
    //  ControllerがそのRegionから、座標を検索し、popupを出す
    this->getViewController()->showRegion(Region(0,0,0,0));


}
void MapView::mouseDoubleClickEvent(QMouseEvent *) {

}

