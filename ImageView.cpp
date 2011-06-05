#include "imageview.h"

ImageView::ImageView(QWidget *parent) :
    QWidget(parent) {

}

ImageView::~ImageView() {
    delete image_;
}

void ImageView::setImage(QPixmap *image) {
    if ( image != NULL ) {
        image_ = new QPixmap(*image);
        this->setGeometry(0, 0, this->getImage()->width(), this->getImage()->height());
    } else {
        image_ = NULL;
    }
}

QPixmap *ImageView::getImage() {
    return image_;
}

//  privates

void ImageView::paintEvent(QPaintEvent *e) {
    if ( this->getImage() != NULL ) {
        QPainter painter(this);
        painter.drawPixmap(0,0,*(this->getImage()));
    }
}
