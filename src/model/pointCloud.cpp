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
void CloudComponent::setProjectionType(std::shared_ptr<ProjectionType> pTyp){throw std::runtime_error ("Cannot setProjectionType - Operation not supported for this cloudType class");}
void CloudComponent::setSegmentationType(std::shared_ptr<SegmentationType> sTyp){throw std::runtime_error ("Cannot setSegmentationType - Operation not supported for this cloudType class");}
void CloudComponent::setClassificationType(std::shared_ptr<ClassificationType> cTyp){throw std::runtime_error ("Cannot setClassificationType - Operation not supported for this cloudType class");}
void CloudComponent::setBenchmarkType(std::shared_ptr<BenchmarkType> benchamrkType,int objectID){}
void CloudComponent::setBenchmarkType(std::shared_ptr<BenchmarkType> bType){
    this->benchmarkType=bType;
}

CloudComponent* CloudComponent::getCloud(int object_ID){
    return nullptr;
}
std::vector<std::string> CloudComponent::getCloudsNames(){
    throw std::runtime_error ("Cannot getCloudNames() - Operation not supported for this cloudType class");
    return {};
}
std::vector<int> CloudComponent::getCloudsClassIDs(){
    std::cout<<"Cannot getCloudsClassIDs - Operation not supported for this cloudType class"<<std::endl;
    return {};
}
int CloudComponent::getCloudClassID(){
    std::cout<<"Cannot getCloudClassID - Operation not supported for this cloudType class"<<std::endl;
    return -2;
}
std::vector<float> CloudComponent::getNNResopneVector(){return {};}
int CloudComponent::getNumberOfClouds(){
    return 0;
}
std::size_t CloudComponent::getCloudSize(){
    std::cout<<"Cannot getCloudSize() - Operation not supotted for this cloudType class"<<std::endl;
    return 0;
}
std::string CloudComponent::getCloudClassName(){
    if(benchmarkType!=nullptr){
        return this->benchmarkType->mapClass(this->getCloudClassID());
    }else{
        return "No benchmarkType set (class mapping not set)";
    }

}
int CloudComponent::getCloudID(){
    std::cout<<"Cannot getCloudID - Operation not supported for this cloudType class"<<std::endl;
    return -2;
}
std::vector<int> CloudComponent::getCloudsIDs(){
    std::cout<<"Cannot getCloudsIDs() - Operation not supported for this cloudType class"<<std::endl;
    return {};
}
void CloudComponent::saveCloud(std::string FILEPATH){
    std::cout<<"Cannot saveCloud() - operation not suppoerted for this cloudType"<<std::endl;
}
CloudComponent* CloudComponent::getCloud(){
    return this;
}
size_t CloudComponent::getCloudNumberOfPoints(){
    if(this->cloud!=nullptr){
        return this->cloud->size();
    }else{
        return 0;
    }
}
cloudType CloudComponent::getCloudType(){
    return this->type;
}
std::string CloudComponent::getName(){
    return  this->name;
}
std::string CloudComponent::getSourcePath(){
    return this->sourcePath;
}
std::string CloudComponent::getParentSceneName(){
    return this->parentSceneName;
}
std::string CloudComponent::getParentSourcePath(){
    return this->parentSourcePath;
}
void CloudComponent::setParentSourcePath(std::string parentSrcPath){
    this->parentSourcePath=parentSrcPath;
}

void CloudComponent::setController(std::shared_ptr<PointCloudController> ctr){std::cout<<"Could not setController - Operation not supported for this cloudType class"<<std::endl;}
void CloudComponent::updateView(){std::cout<<"Could not updateView - Operation not supported for this cloudType class"<<std::endl;}

void CloudComponent::clearProjections(){}
//////////////////////////////////////////////////////////////

CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,int id):CloudComponent(_cloud,"object"){ //->?czyli domyslna nazwa obiektu jest "object"
    this->id=id;
    this->type=type_CloudObject;
} //->? NAUKA - przekazywanie parametrow do konstruktora bazowego
CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name):CloudComponent(_cloud,_name){
    //# co z id w przypadku tego konstruktora ?
    this->type=type_CloudObject;
}
CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path):CloudComponent(_cloud,_name,src_path){
    this->type=type_CloudObject;
}
CloudObject::CloudObject(pcl::PointCloud<pcl::PointXYZ>::Ptr _cloud,std::string _name,std::string src_path,std::string parName, std::string parSrcPath,int id_,int cls_id,std::vector<float> nnRespVec)
    :CloudComponent(_cloud,_name,src_path,parName,parSrcPath)
{
    this->type=type_CloudObject;
    this->id=id_;
    this->class_id=cls_id;
    this->nnResponseVector=nnRespVec;
}
void CloudObject::setProjectionType(std::shared_ptr<ProjectionType> pTyp){
    this->projectionType=pTyp;
}
void CloudObject::setClassificationType(std::shared_ptr<ClassificationType> cTyp){
    this->classificationType=cTyp;
}
void CloudObject::project(std::shared_ptr<ProjectionType> projTyp) {
    setProjectionType(projTyp);
    if(projectionType!= nullptr){
        std::cout<<"PROJECTING "<<name<<" "<<id<<std::endl;
        projections=projectionType->project(this->cloud);
    } else{
        throw std::runtime_error ("Set projectionType for CloudObject class first!");
    }
}
void CloudObject::edit(std::shared_ptr<EditType> eType){
    if(eType!=nullptr){
        eType->edit(this->projections); //we pass projections by reference so we are editing this class "projections" member
    }
}
void CloudObject::classify(std::shared_ptr<ClassificationType> cTyp,std::string modelDir,int numOfClasses) {
    this->classificationType=cTyp;
    if(classificationType!= nullptr){
        std::cout<<"CLASSIFYING "<<name<<" "<<id<<std::endl;
        //this->class_id=classificationType->classify(this->projections,modelDir,numOfClasses);
        this->nnResponseVector=classificationType->classifyAndGetNNResponeVector(this->projections,modelDir,numOfClasses); //returns vector-> vecotr[0]=classification result=classID, the rest of vector is a NeuralNet response vector
        if(!nnResponseVector.empty()){
            this->class_id=static_cast<int>(nnResponseVector.at(0));
            this->nnResponseVector=std::vector<float>(this->nnResponseVector.cbegin()+1,this->nnResponseVector.cend());
        }

        clearProjections();

        updateView();
    } else{
        throw std::runtime_error ("Set classificationType for CloudObject class first!");
    }
}
void CloudObject::classify(std::shared_ptr<ClassificationType> cTyp,std::shared_ptr<SegmentationType> sTyp,std::shared_ptr<ProjectionType> pTyp,std::shared_ptr<EditType> eTyp, std::string modelDir,int numOfClasses){
    project(pTyp);
    edit(eTyp);
    classify(cTyp,modelDir,numOfClasses);
}
void CloudObject::benchmark(std::shared_ptr<BenchmarkType> bType,std::string FILEPATH){
    std::cout<<"ADDING BENCHMARK LABEL FOR "<<name<<" CLOUD"<<std::endl;
    bType->setFileName(this->parentSceneName);
    bType->setFilePath(FILEPATH);
    this->benchmarkType=bType;
    bType->benchmark(this->cloud,this->class_id);
    updateView();
}
void CloudObject::visualize(std::shared_ptr<VisualizationType> vTyp,pcl::visualization::PCLVisualizer::Ptr viewer){
    vTyp->visualize(this->cloud,this->class_id,this->name,viewer);
}
void CloudObject::visualize(){
    std::cout<<"To be defined"<<std::endl;
    //...
}
void CloudObject::saveCloud(std::string FILEPATH){
    FILEPATH=FILEPATH+"/"+this->name;
    if(!ends_with(this->name,".pcd")){
            FILEPATH=FILEPATH+".pcd";
    }
    std::cout<<"Saving cloud to"<<FILEPATH<<std::endl;
    pcl::io::savePCDFileASCII (FILEPATH, *cloud);
}
void CloudObject::saveClouds(std::string FILEPATH){
    saveCloud(FILEPATH);
}
void CloudObject::saveProjections(std::string FILEPATH){
    for(int i=0; i<projections.size();++i){
        cv::imwrite(FILEPATH+"/"+name+
        /*"_"+std::to_string(id)*/
        /*TU POWIENNO BYC: NUMER ALBO KAT RZUTU W PIONIE I POZIOMIE, TYMCZASOWO DAJE PO PROSTU NUMER RZUTU*/
        this->projectionType->getProjectionNameSuffix(i)+".jpg",projections.at(i));
    }
}
void CloudObject::setName(std::string name){this->name=name;}
void CloudObject::setParentSceneName(std:: string name){this->parentSceneName=name;}
std::vector<std::string> CloudObject::getCloudsNames(){
    return {};
}
int CloudObject::getCloudClassID(){
    return this->class_id;
}
int CloudObject::getCloudID(){
    return this->id;
}
/**
 * @brief CloudObject::getNNResopneVector
 * @return response vector of neural net (without id of max response = class_id)
 */
std::vector<float> CloudObject::getNNResopneVector(){
    if(this->nnResponseVector.size()>=1){
        return this->nnResponseVector;
    }else{
        return {};
    }
}
std::size_t CloudObject::getCloudSize(){
    return sizeof(pcl::PointXYZ)*this->cloud->size();
}

void CloudObject::setController(std::shared_ptr<PointCloudController> ctr){
    this->controller=ctr;
}
void CloudObject::updateView(){
    if(this->controller!=nullptr){
        this->c