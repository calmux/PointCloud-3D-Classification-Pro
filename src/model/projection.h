//
// Created by radek on 15.03.19.
//

#ifndef INC_3DPOINTCLOUDCLASSIFICATION_PROJECTION_H
#define INC_3DPOINTCLOUDCLASSIFICATION_PROJECTION_H

#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <opencv2/opencv.hpp>
#include <pcl/range_image/range_image_planar.h>
#include <string>
struct ProjectionParameters{ //# NAUKA-> CZYTAJ: https://stackoverflow.com/questions/4203010/how-to-initialize-member-struct-in-initializer-list-of-c-class
    ProjectionParameters(double min_deg,double max_deg , int n, double min_h, double max_h,int n_h);
    double min_h=0;  //min observation angle vertically
    double max_h=0; //max -||-
    //#zrob jakos tak, zeby wartosci min_h max_h itd. nie mozna bylo zmiennic przez przypadek (zeby tylko sie dalo przez konstruktor lub przez f. setParametes())_
    int n_h=1;// number of vertical angles at witch we want to project object

    double min_deg=0;// for horizontal observations, analogously as for vertical
    double max_deg=0;
    int n=1;// number of horizontal angles at witch we want to project object
};

class ProjectionType{
protected:
    ///->? Uwaga - tu mozna rozwazyc deklaracje niektorych zmiennych (np. alfa_deg) jako static, poniewaz nie musimy tworzyc nowych tych zmiennych przey inicjalizowaniu nowego obiektu tej klasy
    ///moze to miec znaczenie chyba dla wydajnosci, jezeli towrzylibysmy duzo obiektow tej klasy -> ale ostateczenie nie towrzymy przeciez duzo obiektow typu ProjectionType wiec raczej nie stanowi problemu, ze nie uzwywamy static
    st