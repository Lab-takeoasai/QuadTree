#include "mapview.h"
#include "stdio.h"
//#include "region.hpp"


#include "imageview.h"

MapView::MapView(QWidget *parent) :
    QWidget(parent)
{
    this->setImage(NULL);
//    this->setRegion(NULL);
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
//    if ( this->getRegion() )
 //       delete region_;
}

/*
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
*/


//  privates

void MapView::paintEvent(QPaintEvent *e) {
    if ( this->getImage() != NULL ) {
        QPainter painter(this);
        painter.drawPixmap(0,0,*(this->getImage()));
    }
}

void MapView::mousePressEvent(QMouseEvent *) {
    printf("mouse press event");
    ImageView *imageView = new ImageView();
    imageView->setImage(this->getImage());
    imageView->show();
}
void MapView::mouseDoubleClickEvent(QMouseEvent *) {

}

