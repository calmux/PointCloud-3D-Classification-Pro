//
// Created by radek on 14.03.19.
//
#include "src/model/pointCloud.h"
#include <pcl/io/pcd_io.h>
#include <opencv2/opencv.hpp>

CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name):cloud(_cloud),name(_name){}
CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path):cloud(_cloud),name(_name),sourcePath(src_path){}
CloudComponent::CloudComponent(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path,std::string parName, std::string parSrcPath)
    :cloud(_cloud),name(_name),sourcePath(src_path),parentSceneName(parName),parentSourcePath(parSrcPath){}

void CloudComponent::setFactory(std::shared_ptr<CloudObjectFactory> fc){
    std::cout<<"Cannot setFactory(CloudObjectFactory) for this cloudType. Operation is supported for scenes."<<std::endl;
}

void CloudComponent::segment(std::shared_ptr<SegmentationType> segmentationType){}//{ std::cout<<"Cannot segment - Operation not supported for this cloudType class";}
void CloudComponent::project(std::shared_ptr<ProjectionType> projTyp){ throw std::runtime_error ("Operation not supported for this cloudType class");}
void CloudComponent::project(std::shared_ptr<ProjectionType> projTyp, int objectID){ throw std::runtime_error ("Operation not supported for this cloudType class");}
void CloudComponent::edit(std::shared_ptr<EditType> eType){throw std::runtime_error ("Cannot edit - Operation not supported for this cloudType class");}
void CloudComponent::edit(std::shared_ptr<EditType> eType, int objectID){throw std::runtime_error ("Cannot edit - Operation not supported for this cloudType class");}
void CloudComponent::classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses){ throw std::runtime_error ("Cannot classify - operation not supported for this cloudType class");}
//# przemysl implementacje ponizszej funkcji dla CloudObject
void CloudComponent::classify(std::shared_ptr<ClassificationType> cTyp,std::shared_ptr<SegmentationType> sTyp,std::shared_ptr<ProjectionType> pTyp,std::shared_ptr<EditType> eTyp, std::string modelDir,int numOfClasses){}
void CloudComponent::classify(std::shared_ptr<ClassificationType> cTyp, std::string modelDir,int numOfClasses, int object_id){ throw std::runtime_error ("Cannot classify - operation not supported for this cloudType class");}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp){throw std::runtime_error ("Cannot visualize - Operation not supported for this cloudType class");}
void CloudComponent::visualizeAllChildren(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){std::cout<<"Cannot visualize - Operation not supported for this cloudType class";}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){std::cout<<"Cannot visualize - Operation not supported for this cloudType class";}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp,int object_id){throw std::runtime_error ("Cannot visualize - Operation not supported for this cloudType class");}
void CloudComponent::visualize(std::shared_ptr<VisualizationType> vTyp,int object_id,pcl::visualization::PCLVisualizer::Ptr viewer){throw std::runtime_error ("Cannot visualize - Operation not supported for this cloudType class");}
void CloudComponent::benchmark(std::shared_ptr<BenchmarkType> bType, std::string FILEPATH){ throw std::runtime_error ("Operation not supported for this cloudType class");}
void CloudComponent::benchmark(std::shared_ptr<BenchmarkType> bType, std::string FILEPATH,int object_id){ throw std::runtime_error ("Operation not supported for this cloudType class");}

void CloudComponent::addCloud(std::unique_ptr<CloudComponent> cc/*CloudComponent *cc*/){std::cout<<"Cannot addCloud(cc/*CloudComponent *cc*/) - Operation not supported for this cloudType class"<<std::endl;} //when we are adding objects or clouds by one (for example manually)
void CloudComponent::removeCloud(int object_ID){std::cout<<"Cannot removeCloud(object_ID) - Operation not supported for this cloudType class"<<std::endl;}
void CloudComponent::saveClouds(std::string FILEPATH){throw std::runtime_error ("Cannot save - Operation not supported for this cloudType class");}
void CloudComponent::saveClouds(std::string FILEPATH, int object_ID){std::cout<<"Cannot saveCloud(FILEPATH,object_ID)- Operation not supported for this cloudType class"<<endl;}
void CloudComponent::saveProjections(std::string FILEPATH){throw std::runtime_error ("Cannot save - Operation not supported for this cloudType class");}
void CloudComponent::saveProjections(std::string FILEPATH, int objectID){throw std::runtime_error ("Cannot save - Operation not supported for this cloudType class");}
void CloudComponent::setProjectionType(std::shared_ptr<ProjectionType> pTyp){throw std::runtime_error ("Cannot setProjectionType - Operat