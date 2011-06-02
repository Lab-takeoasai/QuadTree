#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "mapview.h"

#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap *image = new QPixmap();
    image->load("/Users/asai/Desktop/image.jpg");

    MapView *mapView = new MapView(this);
    mapView->setGeometry(0,0,300, 500);
    mapView->setImage(image);

}

MainWindow::~MainWindow()
{
    delete ui;
}
