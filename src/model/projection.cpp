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
BinaryProjection::BinaryProjection(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h):ProjectionType(min_deg,max_deg ,n,min_h,max_h,n_h) {
    cloudProjected=pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
}
//BinaryProjection::BinaryProjection(){}
/**
 *
 * double alfa_h -parametr 1 - wysokosc (kat) pod jakim ogladamy obiekt wzdluz jego wysokosci;
 * double alfa_deg -parametr 2 - kat pod jakim ogladamy obiekt wszerz (podajemy w stopniach)
 */
void BinaryProjection::calculateCloudProjected(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud) {
    cloudProjected=pcl::PointCloud<pcl::PointXYZ>::Ptr(new pcl::PointCloud<pcl::PointXYZ>);
    // Create a set of planar coefficients with X=Y=0,Z=1 //kolejne wartosci tablicy, to kolejne paramaetry plasczyzny, na
    //ktora rzutujemy chmure 3D Ax+By+Cz+D=0
    //warto wykorzystac fakt, ze wektor [A,B,C] jest wektorem normalnym do tej plaszczyzny
    //kazdy widok powinien byc skierowany w kierunku centroidu badanego obiektu
    pcl::ModelCoefficients::Ptr coefficients (new pcl::ModelCoefficients ());
    double alfa=0;//zmienna pomocnicza - zamiana kata ze stopni na radiany
    double h=0;


    //pcl::PointXYZ min_pt;
    //pcl::PointXYZ max_pt;
    pcl::getMinMax3D(*cloud, object_min_pt, object_max_pt);
    //wspolrzedne srodka boudingbox'a, mozna ewnetualnie to pozniej zastapic srodkiem ciezkosci obiektu
    double x_c=object_min_pt.x+(object_max_pt.x-object_min_pt.x)/2;
    double y_c=object_min_pt.y+(object_max_pt.y-object_min_pt.y)/2;
    double z_c=object_min_pt.z+(object_max_pt.z-object_min_pt.z)/2;

    double x_s=0,y_s=0,z_s=0;//wspolrzedne poczatku ukl. wsp. (bazowego) - sens
    double A0=x_c-x_s;
    double B0=y_c-y_s;
    double C0=0;//min_pt.z+h;
    double D=0;//tu trzeba jeszcze ustalic ile ten parametr powinien wynosic
    //Obrot wektora (A0,B0,C0) o kat alfa (szczegoly patrz w zeszycie) (- wektor A,B,C jest prostopadly do plaszczyzny Ax+By+Cz+D=0)
    alfa=alfa_deg*PI/180; //bo funkcja sin() cos() przyjmuje wartosc w radianach
    double A = (x_c-x_s)*cos(alfa)-(y_c-y_s)*sin(alfa);
    double B = (x_c-x_s)*sin(alfa)+(y_c-y_s)*cos(alfa);
    //okreslenie wspolrzednej C (z) wektora na podstawie podanego kata
    if(alfa_h==90) //wtedy cos bedzie 0 i nie moge korzystac z wzoru
    {
        h=10*(object_max_pt.z-object_min_pt.z); //daje jakas duza wielokrotnosc wysokosci obiektu, zeby efekt byl taki jak 90 st (ogladnie go pionowo od gory)
    }
    else if(alfa_h==-90)   //ogladamy pionowo od dolu
    {
        h=-10*(object_max_pt.z-object_min_pt.z);
    }
    else
    {
        alfa_h=alfa_h*PI/180;//teraz kat obserwacji obiektu w pionie jest w radianach
        h=sqrt((A*A*sin(alfa_h)*sin(alfa_h)+B*B*sin(alfa_h)*sin(alfa_h))/(cos(alfa_h)*cos(alfa_h)));
    }
    double C = h;//min_pt.z+h;
    //cout<<"A = "<<A<<endl;
    //cout<<"B = "<<B<<endl;
    //cout<<"C = "<<C<<endl;
    coefficients->values.resize (4);
    coefficients->values[0] = static_cast<float>(A); //0.8
    coefficients->values[1] = static_cast<float>(B); //0.3
    coefficients->values[2] = static_cast<float>(C); //-0.3
    coefficients->values[3] = static_cast<float>(D); //0

    // Create the filtering object
    pcl::ProjectInliers<pcl::PointXYZ> proj;
    proj.setModelType (pcl::SACMODEL_PLANE);
    proj.setInputCloud (cloud);
    proj.setModelCoefficients (coefficients);
    proj.filter (*cloudProjected);

    //TRANSFORMACJA z XYZ do XY:
    pcl::PointXYZ min_pt_proj;
    pcl::PointXYZ max_pt_proj;
    pcl::getMinMax3D(*cloudProjected, min_pt_proj, max_pt_proj);
    pcl::PointXYZ P, P1; //P1 wyznacza wektor PP1 ktory okreskla os y' , P - punkt srodkowy chmury
    double t;//zmienna pomocnicza

    //P to punkt srodkowy chmury -  ale czy to oznacza tez srodek obrazu na rzutowanej plaszczyznie ??
    P.x=min_pt_proj.x+(max_pt_proj.x-min_pt_proj.x)/2;
    P.y=min_pt_proj.y+(max_pt_proj.y-min_pt_proj.y)/2;
    P.z=min_pt_proj.z+(max_pt_proj.z-min_pt_proj.z)/2;

    if(-A*A-B*B != 0){t=(max_pt_proj.z-P.z)/(-A*A-B*B);}
    else{
        cout<<"Blad - dziel. przez 0";
    }
    //A i B nie moga wiec byc rownoczesnie rowne 0 -> plaszczyzne rownolegla
    //do podloza  (na ktora robie projekcje)-> nalezy postapic inaczej
    P1.x=P.x+t*(A*C);
    P1.y=P.y+t*(B*C);
    P1.z=max_pt_proj.z;


    Eigen::Affine3f transformation;
    //transformation=transformation.;
    Eigen::VectorXf from_line_x, from_line_y, to_line_x, to_line_y;
    Eigen::Vector3f vector_y,vector_x, vector_z;// to sa wektroy wyznaczajace kierunek osi ukladu do ktorego transforumjemy chmure
    from_line_x.resize(6); from_line_y.resize(6);
    to_line_x.resize(6); to_line_y.resize(6);

    vector_z[0]=A;
    vector_z[1]=B;
    vector_z[2]=C;

    vector_y[0]=P1.x-P.x;
    vector_y[1]=P1.y-P.y;
    vector_y[2]=P1.z-P.z;

    vector_x=vector_y.cross(vector_z);
    //normalizacja - inaczej nie dziala funkcja transformBetween2CordinateSystems
    vector_x.normalize();
    vector_y.normalize();
    vector_z.normalize();
    //cout<<"vector_x: "<<vector_x[0]<<" "<<vector_x[1]<<" "<<vector_x[2]<<endl;
    //cout<<"vector_y: "<<vector_y[0]<<" "<<vector_y[1]<<" "<<vector_y[2]<<endl;
    from_line_x << 0, 0, 0, 1, 0, 0;
    from_line_y << 0, 0, 0, 0, 1, 0;
    //to_line_x << 10, -5, 1, 1, 0, 0;
    //to_line_y << 10, -5, 1, 0, 1, 0;
    to_line_x << P.x,P.y,P.z,vector_x[0],vector_x[1],vector_x[2];
    to_line_y << P.x,P.y,P.z,vector_y[0],vector_y[1],vector_y[2];


    if(pcl::tran