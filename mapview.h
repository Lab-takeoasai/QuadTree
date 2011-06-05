#ifndef MAPVIEW_H
#define MAPVIEW_H

#include <QWidget>
#include <QPainter>
#include <QPixmap>

class Region;
class MapViewController;
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
    void setViewController(MapViewController *reg);
    MapViewController *getViewController();

private:    //  functions
     void paintEvent(QPaintEvent *e);   //  drawView
     void mousePressEvent(QMouseEvent *);
     void mouseDoubleClickEvent(QMouseEvent *);

signals:

public slots:

private:    //  vars
    QPixmap *image_;
    Region *region_;
    MapViewController *viewController;
};

#endif // MAPVIEW_H
