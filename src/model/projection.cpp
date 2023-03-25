//
// Created by radek on 15.03.19.
//
#include "src/model/projection.h"

#include <pcl/common/common.h>//do getMinMax3D
#include <pcl/ModelCoefficients.h>
#include <pcl/filters/project_inliers.h>
#include <pcl/common/eigen.h>//do uzyskania macierzy transformacji (bool pcl::transformBetween2CoordinateSystems)
#include <pcl/common/transforms.h> //do transformacji chmury ( pcl::transformPointCloud) z wykorzystaniem macierzy transformacji
#include <pcl/visualization/range_image_visualizer.h>
#include <cmath>

#define PI 3.14159265

ProjectionParameters::ProjectionParameters(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h):
min_deg(min_deg),
max_deg(max_deg),
n(n),
min_h(min_h),
max_h(max_h),
n_h(n_h){}

//double ProjectionType::alfa_deg=0;
ProjectionType::ProjectionType(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h)
:projParam(min_deg,max_deg,n,min_h,max_h,n_h){}
//ProjectionType::ProjectionType(){}
std::vector<cv::Mat> ProjectionType::project(pcl::PointCloud<pcl::Poi