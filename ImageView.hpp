#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

namespace Ui {
    class ImageView;
}

class ImageView : public QGraphicsView
{

public:
    ImageView( QWidget *parent );
    void mousePressEvent(QMouseEvent* event);
public:
    double centerX;
    double centerY;
    double r;

private:
};

#endif // MAINWINDOW_H
