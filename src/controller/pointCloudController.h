﻿#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883
#ifndef INC_3DPOINTCLOUDCLASSIFICATION_POINTCLOUDCONTROLLER_H
#define INC_3DPOINTCLOUDCLASSIFICATION_POINTCLOUDCONTROLLER_H

#include "src/model/cloudFactory.h"
class MainWindow;
#include "src/view/mainwindow.h"

class CloudComponent;
class CloudScene;
class CloudObject;
#include "src/model/pointCloud.h"
class SaveLoad;
#include "src/view/saveLoad.h"
#include <limits>

class PointCloudController: public std::enable_shared_from_this<PointCloudController> //#//https://stackoverflow.com/questions/27894246/cast-this-to-stdshared-ptr
{
private:
    std::vector<std::unique_ptr<CloudComponent>> cachedClouds;
    std::shared_ptr<CloudSceneFactory> sceneFactory;
    std::shared_ptr<CloudObjectFactory> objectFactory;
    std::shared_ptr<BoundingBoxType> boundingBox;
    std::shared_ptr<VisualizationType> visualization;
    std::shared_ptr<SaveLoad> saveLoad;
    QTreeWidget *treeWidgetObserver;
    QVTKWidget *qVTKWidgetObserver;
    pcl::visualization::PCLVisualizer::Ptr viewerObserver;
    int cachedCloudScenesLimit=2;
    std::size_t cachedCloudsMemoryLimit=10000; //in MB
    int treeWidgetNameColumnID=0;
    int treeWidgetCloudTypeID=1;
    int treeWidgetClassIDColumnID=2;
    int treeWidgetClassNameColumnID=3;
    int treeWidgetNNResponseVectorColumnID=4;
public:
    PointCloudController();
    int getTopLevelIndexOfSelectedCloud(QTreeWidgetItem* item); //# funkcja nie edytuje orginalnych danych (item), ale zeby to podkreslic wartobyloby dac const -> to skolei powoduje inne problemy)
    QTreeWidgetItem* getChildItemWithID(QTreeWidgetItem* parent,int id);
    QTreeWidgetItem* getTopLevelItem(QTreeWidgetItem* item);//#funkcja nie edytuje orginalnych danych (item), ale zeby to podkreslic wartobyloby dac const -> to skolei powoduje inne problemy)
    void registerQTreeWidgetObserver(QTreeWidget *treeWidgetObserver);
    void registerQVTKidgetObserver(QVTKWidget *QVTKWidgetObserver);
    void registerPCLViewerObserver(pcl::visualization::PCLVisualizer::Ptr viewOb);
    std::size_t getMemoryUsageOfCachedClouds();
    void setCachedCloudsMemoryLimit(std::size_t limit);
    v