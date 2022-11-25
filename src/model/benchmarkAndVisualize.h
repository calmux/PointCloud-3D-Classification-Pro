//
// Created by radek on 21.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_BENCHMARKANDVISUALIZE_H
#define INC_3DPOINTCLOUDCLASSIFICATION_BENCHMARKANDVISUALIZE_H
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/features/moment_of_inertia_estimation.h>
#include <pcl/common/common.h>//do getMinMax3D
#include <fstream> //->?do zapisywania do pliku .txt
#include <pcl/visualization/pcl_visualizer.h>
#include <pcl/visualization/cloud_viewer.h>
enum BBType{type_AxisAlignedBoundingBox, type_OrientedBoundingBox, type_NotSpecified};

class BoundingBoxType{
protected:
    pcl::PointXYZ min_point;
    pcl::PointXYZ max_point;
    pcl::PointXYZ center; //->? ustaw paramtery domyslne ! np. #include <limits> + center=std::numeric_limits<float>::quiet_NaN();
    float l=-1; //object (or max bounding box when using AABB) length
    float w=-1; //
    float h=-1;
    float yaw;//->? ustaw paramtery domyslne ! np. #include <limits> + center=s