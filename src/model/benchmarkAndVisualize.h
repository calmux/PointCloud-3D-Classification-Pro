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
    float yaw;//->? ustaw paramtery domyslne ! np. #include <limits> + center=std::numeric_limits<float>::quiet_NaN();
    BBType bbType = type_NotSpecified;
public:
    explicit BoundingBoxType(BBType type);
    virtual void calculate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)=0;
    pcl::PointXYZ getMinPt();
    pcl::PointXYZ getMaxPt();
    pcl::PointXYZ getCenter();
    float getLength();
    float getWidth();
    float getHeight();
    float getYaw();
    BBType getType();
    virtual Eigen::Quaternionf getQuaternionf();
    virtual Eigen::Vector3f getOBB_positionV3f();
};
class AxisAlignedBoudningBox:public BoundingBoxType{
public:
    AxisAlignedBoudningBox();
    void calculate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
};
class OrientedBoundingBox:public BoundingBoxType{
private:
    BBType bbType = type_OrientedBoundingBox;
    Eigen::Quaternionf OBB_quaternion;//wykorzystywane tylko do rysowania boundingboxa (funkcja addCube z kwaternionem)
    Eigen::Vector3f OBB_positionV3f;//wykorzystywane tylko do rysowania boundingboxa (funkcja addCube z kwaternionem)
public:
    OrientedBoundingBox();
    void calculate(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud);
    Eigen::Quaternionf getQuaternionf();
    Eigen::Vector3f getOBB_positionV3f();
};

class BenchmarkType{
protected:
    std::shared_ptr<BoundingBoxType> boundingBox;
    bool class_mapping_set=false;
    std::vector<std::string> classList;
    int class_id=-1;
    std::string FILEPATH=""; //path to the labels.txt folder
    std::string FILENAME="object_labels.txt";
public:
    explicit BenchmarkType(std::shared_ptr<BoundingBoxType> bBox);
    virtual void calculateParameters(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud)=0;
    virtual void saveTxt()=0;
    void setFileName(std::string fName);
    void setFilePath(std::string fPath);
    void setClassMapping(std::vector<std::string> classList); //classList - on i't