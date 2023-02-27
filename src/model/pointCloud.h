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
#include 