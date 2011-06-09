#include "mapview.h"

#include "stdio.h"

#include "imageview.h"

#include "region.hpp"
#include "location.hpp"

#include "mapviewcontroller.h"


#include <QMouseEvent>


//  privates

void MapView::paintEvent(QPaintEvent *e) {
    if ( this->getImage() != NULL ) {
        QPainter painter(this);
        painter.drawPixmap(0,0,*(this->getImage()));
    }

    if ( this->getLocations() != NULL ) {
        Region *r = this->getRegion();
        double dx = r->width/2.0;
        double dy = r->height/2.0;

        QPainter painter(this);
        QRect rect = painter.viewport();
//        painter.setViewport(rect.x(), rect.y(), rect.width(),rect.height());

        painter.setPen(Qt::red);
        painter.setWindow(r->getMinX(), r->getMinY(), r->width, r->height);
//        painter.setViewport(r->getMinX(), r->getMinY(), r->width, r->height);
        for ( unsigned int i = 0; i < this->getLocations()->size(); i++ ) {
            //  TODO: width / 10, height / 10を検索範囲にしてあるので、適切に変更すること
            Location *l = this->getLocations()->at(i);
            painter.drawEllipse(r->x, r->y, dx, dy);
//            printf("(%f, %f), (%f, %f)", r->x + r->width/2.0, r->y + r->height/2.0, r->width/10.0, r->height/10.0);
            painter.drawPoint(r->x, r->y);


        }
        painter.drawLine(r->getMaxX(), r->getMaxY(), r->getMinX(), r->getMinY());
    }
}

void MapView::mousePressEvent(QMouseEvent *e) {

    Region *r = this->getRegion();
    double x = r->x + (r->width * ((double)e->x() / this->width() - 0.5));
    double y = r->y + (r->height * ((double)e->y() / this->height() - 0.5));

    //  TODO: width / 10, height / 10を検索範囲にしてあるので、適切に変更すること
    //this->getViewController()->showRegion(Region(x, y, r->width/10.0, r->height/10.0));
    this->getViewController()->showRegion(Region(x, y, 1.0, 1.0));


}

void MapView::mouseDoubleClickEvent(QMouseEvent *e) {

}







//  Initializations & decontructer
//  setter & getter

MapView::MapView(QWidget *parent) :
    QWidget(parent)
{
    this->locations = NULL;
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

void MapView::setLocations(std::vector<Location *> *locs) {
    this->locations = locs;
}

std::vector<Location *> *MapView::getLocations() {
    return this->locations;
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
