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
        double w_ratio = ((double)this->width()/r->width);
        double h_ratio = ((double)this->height()/r->height);

        QPainter painter(this);
        QMatrix matrix;
        matrix.setMatrix(w_ratio, 0, 0, -h_ratio, this->x() - w_ratio * r->getMinX(), this->y() + this->height() + h_ratio * r->getMinY());
        painter.setWorldMatrix(matrix);
        painter.setPen(Qt::red);

        for ( unsigned int i = 0; i < this->getLocations()->size(); i++ ) {
            Location *l = this->getLocations()->at(i);
            painter.drawPoint(QPointF(l->x, l->y));
        }
        //painter.drawLine(QPointF(140.0, 40.0), QPointF(142.4, 40.0));
        //painter.drawLine(QPointF(140.0, 40.0), QPointF(138.0, 40.0));
        //painter.drawLine(QPointF(140.0, 40.0), QPointF(140.0, 38.0));
        //painter.drawLine(QPointF(140.0, 40.0), QPointF(140.0, 42.4));
    }
}

void MapView::mousePressEvent(QMouseEvent *e) {

}

void MapView::mouseDoubleClickEvent(QMouseEvent *e) {
    Region *r = this->getRegion();
    double x = r->x + (r->width * ((double)e->x() / this->width() - 0.5));
    double y = r->y + (r->height * (0.5 - (double)(e->y() - this->y()) / this->height()));

    //  TODO: width / 10, height / 10を検索範囲にしてあるので、適切に変更すること
    this->getViewController()->showRegion(Region(x, y, r->width/10.0, r->height/10.0));
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
