//
// Created by radek on 14.03.19.
//
#pragma once //without this line this problem appears: https://bugreports.qt.io/browse/QTCREATORBUG-20883

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_POINTCLOUD_H
#define INC_3DPOINTCLOUDCLASSIFICATION_POINTCLOUD_H

#include <string>
#include <vector>
#include <memory>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <opencv2/opencv.hpp>

#include "src/model/projection.h"
#include "src/model/cloudFactory.h"
#include "src/model/segmentation.h"
#include "src/model/classification.h"
#include "src/model/benchmarkAndVisualize.h"
#include "src/model/edit.h"
class PointCloudController;
#include "src/controller/pointCloudController.h"

class CloudObjectFactory;
class CloudSceneFacory;

enum cloudType{type_CloudScene, type_CloudObject};

class CloudComponent{
protected:
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud;
    cloudType type;
    std::shared_ptr<BenchmarkType> benchmarkType=nullptr;
    std::string name="default name";
    std::string sourcePath="";
    std::string parentSceneName="";
    std::string parentSourcePath="";

    std::shared_ptr<PointCloudController> controller=nullptr;
public:
    CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud,std::string _name);
    CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path);
    CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path,std::string parName, std::string parSrcPath);
    virtual void setFactory(std::shared_ptr<CloudObjectFactory> fc);

    virtual void segment(std::shared_ptr<SegmentationType> segmentationType);
    virtual void project(std::shared_ptr<ProjectionType> projTyp);
    virtual void project(std::shared_ptr<ProjectionType> projTyp, int objectID);
    virtual void edit(std::shared_ptr<EditType> eType);
    virtual void edit(std::shared_ptr<EditType> eType, int objectID);
    virtual void classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses);
    virtual void classify(std::shared_ptr<ClassificationType> cTyp,std::shared_ptr<SegmentationType> sTyp,std::shared_ptr<ProjectionType> pTyp,std::shared_ptr<EditType> eTyp, std::string modelDir,int numOfClasses);
    virtual void classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses,int object_id);
    virtual void benchmark(std::shared_ptr<BenchmarkType> bType,std::string FILEPATH);
    virtual void benchmark(std::shared_ptr<BenchmarkType> bType,std::string FILEPATH,int object_id);
    virtual void visualize(std::shared_ptr<VisualizationType> vTyp);
    virtual void visualizeAllChildren(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer);
    virtual void visualize(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer);
    virtual void visualize(std::shared_ptr<VisualizationType> vTyp,int object_id);
    virtual void visualize(std::shared_ptr<VisualizationType> vTyp,int object_id,pcl::visualization::PCLVisualizer::Ptr viewer);

    virtual void addCloud(std::unique_ptr<CloudComponent> cc/*CloudComponent *cc*/); //when we are adding objects or clouds by one (for example manually)
    virtual void removeCloud(int object_ID);
    virtual void saveCloud(std::string FILEPATH);
    virtual void saveClouds(std::string FILEPATH);
    virtual void saveClouds(std::string FILEPATH, int object_ID);
    virtual void saveProjections(std::string FILEPATH);
    virtual void saveProjections(std::string FILEPATH, int objectID);
    virtual void setProjectionType(std::shared_ptr<ProjectionType> pTyp);
    virtual void setSegmentationType(std::shared_ptr<SegmentationType> sTyp);
    virtual void setClassificationType(std::shared_ptr<ClassificationType> cTyp);
    virtual void setBenchmarkType(std::shared_ptr<BenchmarkType> benchamrkType,int objectID);
    void setBenchmarkType(std::shared_ptr<BenchmarkType> benchamrkType);

    virtual CloudComponent* getClo