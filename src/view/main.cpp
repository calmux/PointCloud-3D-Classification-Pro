#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    std::shared_ptr<PointCloudController> cloudsController =std::make_shared<PointCloudController>();
    std::shared_ptr<ThreadController> threadContr