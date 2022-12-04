
//
// Created by radek on 16.03.19.
//
#ifndef INC_3DPOINTCLOUDCLASSIFICATION_CLOUDFACTORY_H
#define INC_3DPOINTCLOUDCLASSIFICATION_CLOUDFACTORY_H
class PointCloudController;
#include "src/model/pointCloud.h"
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
class CloudObject;
class CloudScene;
class CloudComponent;
/*
class AbstractCloudFactory{
public:
    virtual std::vector<std::shared_ptr<CloudObject>> create(const std::vector<pcl::PointCloud<pcl::PointXYZ>::Ptr>  &clouds, const std::string parentSceneName);