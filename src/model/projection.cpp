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
std::vector<cv::Mat> ProjectionType::project(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {throw std::runtime_error ("Projection operation not supported for this class");}
void ProjectionType::setVerticalAngle(double va){this->alfa_h=va;}
void ProjectionType::setHorizontalAngle(double ha){this->alfa_deg=ha;}
void ProjectionType::setImageHeight(int height){this->w=height;}
void ProjectionType::setImageWidth(int width){this->k=width;}
void ProjectionType::setParameters(double min_deg, double max_deg, int n, double min_h, double max_h, int n_h) {
    this->projParam.min_deg=min_deg;
    this->projParam.max_deg=max_deg;
    this->projParam.n=n;
    this->projParam.min_h=min_h;
    this->projParam.max_h=max_h;
    this->projParam.n_h=n_h;
}
void ProjectionType::calculateStep() {
    if(projParam.n>=2)
        step=(projParam.max_deg-projParam.min_deg)/ static_cast<double>(projParam.n);
    else
        step=0;  //czyli jak n=1 to robimy tylko rzut dla h=min_h

    if(projParam.n_h>=2)
        step_h=(projParam.max_h-projParam.min_h)/ static_cast<double>(projParam.n_h);
    else
        step_h=0;
}
std::vector<cv::Mat> ProjectionType::getProjections(){return projections;}
std::vector<pcl::PointXYZ> ProjectionType::getObjectMinMaxPt(){
    std::vector<pcl::PointXYZ> min_max;
    min_max.push_back(object_min_pt);
    min_max.push_back(object_max_pt);
    return min_max;
}
/**
 * projectionID - projection id, from 0 to (total_projection_number)-1
 * @param projectionID
 * @return
 */
std::string ProjectionType::getProjectionNameSuffix(int projectionID){
    std::stringstream suffix;
    suffix.str("");
    if(projectionID<(projParam.n*projParam.n_h)){
        //#NA RAZIE podaje tu tylko NUMER PORJEKCJI w PIONIE I POZIOMIE, ale w przyszlosci mozna zamiast tego dawac KONKRETNY KAT OBSERWACJI W PIONIE I POZIOMIE
        suffix<<"_p"<<std::to_string(projectionID)<<"_v"<<setw(2) << setfill('0')<<floor(static_cast<double>(projectionID)/ static_cast<double>(projParam.n))
        <<"_h"<<setw(3) << setfill('0')<<projectionID%projParam.n; //v-vertical, h-horizontal
    }
    else{//
        std::cout<<"Given projection ID is to big (there is no such projection)"<<std::endl;
    }
    return suffix.str();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BinaryProjection::BinaryProjection(double min_deg,double max_deg , int n, double min_h, double max_h,in