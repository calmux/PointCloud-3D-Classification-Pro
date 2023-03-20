//
// Created by radek on 26.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_PREPAREDATASET_H
#define INC_3DPOINTCLOUDCLASSIFICATION_PREPAREDATASET_H

#include <string>
class CloudObject;
class CloudObjectFactory;
class CloudSceneFactory;
#include "src/model/pointCloud.h"
#include <boost/filesystem.hpp> //for recursive directory traversing
//#include <omp.h>

class PrepareDataset {
public:
    PrepareDataset(std::string inP, std::string out