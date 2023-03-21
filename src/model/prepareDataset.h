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
    PrepareDataset(std::string inP, std::string outP);
    bool containsCls(std::string cls);
    void setInPath(std::string inP);
    void setOutPath(std::string outP);
    void setClassesOfInterest(std::vector<std::string> classes);
protected:
    std::string inPath;
    std::string outPath;
    std::vector<std::string> classesOfInterest={};
    std::vector<std::tuple<std::string,std::string,std::string>> getPathAndNameAndParentFolderName(const std::string extension=".pcd",bool removeExtensionFromName=true);
};
class PrepareDatasetFrom3D:public PrepareDataset{
protected:
    std::shared_ptr<CloudObject> object=nullptr;
    std::shared_ptr<CloudObjectFactory> factory=nullptr;
    std::shared_ptr<ProjectionType> projection=nullptr;
    std::vector<std::string> fnames; //fnames of 3D objects
    uint TOTAL_PROJECTIONS;
    uint default_num_of_proj_per_obj=36;
    double START_DEGREE=0;
    double END_DEGREE=360;
    double START_v=0;
    double END_v=0;
    int N_v=1;
    //bool RANGE_I