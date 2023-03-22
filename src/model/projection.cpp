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