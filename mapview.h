#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>
#include "QuadTree.hpp"

class MapView : public QWidget
{
    Q_OBJECT
public:     //  functions
    explicit MapView(QWidget *parent = 0);
    ~MapView();

    void setImage(QPixmap *image);
    QPixmap *getImage();
    void setRegion(Region *reg);
    Region *getRegion();

private:    //  functions
     void paintEvent(QPaintEvent *e);   //  drawView
     void mousePressEvent(QMouseEvent *);
     void mouseDoubleClickEvent(QMouseEvent *);

signals:

public slots:

private:    //  vars
    QPixmap *image_;
    Region *region_;
};

#endif // MAPVIEW_H
