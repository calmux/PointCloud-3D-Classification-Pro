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
class