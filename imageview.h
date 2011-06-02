#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

class ImageView : public QWidget
{
    Q_OBJECT
public:
    explicit ImageView(QWidget *parent = 0);
    ~ImageView();

    void setImage(QPixmap *image);
    QPixmap *getImage();
private:
    void paintEvent(QPaintEvent *e);
signals:

public slots:

private:
    QPixmap *image_;
};

#endif // IMAGEVIEW_H
