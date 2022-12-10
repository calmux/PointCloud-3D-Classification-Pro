//
// Created by radek on 14.03.19.
//
#include "src/model/pointCloud.h"
#include <pcl/io/pcd_io.h>
#include <opencv2/opencv.hpp>

CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name):cloud(_cloud),name(_name){}
CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path):cloud(_cloud),name(_name),sourcePath(src_path){}
CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path,std::string parName, std::str