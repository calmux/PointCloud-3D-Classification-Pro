#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883
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
    std