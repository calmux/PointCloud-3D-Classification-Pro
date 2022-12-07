//
// Created by radek on 26.03.19.
//
#include "src/model/edit.h"

ProjectionEdit::ProjectionEdit(cv::MorphShapes kerShape,uint kerWidth, uint kerHeigth):kernelShape(kerShape),kernelWidth(kerWidth),kernelHeight(kerHeigth){}
void ProjectionEdit::edit(std::vector<cv::Mat> &projections){
     //photo editing
     cv::Mat kernel= cv::getStructuringElement(kernelShape,cv::Size(kernelWidth,kernelHeight)); //bez upsampling stosowalem 6,6  //po upsampling 3,3
     ///Canny( vecMat, vec