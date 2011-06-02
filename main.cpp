#include <QtGui/QApplication>
#include "mainwindow.h"

#include "Exif.hpp"
#include "QuadTree.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;


    w.show();

	

    ExifJPEG *exif;
    QuadTree<ExifJPEG> *tree = new QuadTree<ExifJPEG>(exif, Region(50,50,50000000));

    return a.exec();
}
