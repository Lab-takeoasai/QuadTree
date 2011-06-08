#include "mapview.h"

#include "stdio.h"

#include "imageview.h"
#include "region.hpp"
#include "mapviewcontroller.h"


#include <QMouseEvent>


//  privates

void MapView::paintEvent(QPaintEvent *e) {
    if ( this->getImage() != NULL ) {
        QPainter painter(this);
        painter.drawPixmap(0,0,*(this->getImage()));
    }
}

void MapView::mousePressEvent(QMouseEvent *e) {

    Region *r = this->getRegion();
    double x = r->x + (r->width * ((double)e->x() / this->width() - 0.5));
    double y = r->y + (r->height * ((double)e->y() / this->height() - 0.5));

    //  TODO: width / 100, height / 100を検索範囲にしてあるので、適切に変更すること
    this->getViewController()->showRegion(Region(x, y, r->width/100.0, r->height/100.0));


}
void MapView::mouseDoubleClickEvent(QMouseEvent *e) {

}







//  Initializations & decontructer
//  setter & getter

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
