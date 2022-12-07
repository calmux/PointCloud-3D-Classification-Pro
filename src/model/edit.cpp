//
// Created by radek on 26.03.19.
//
#include "src/model/edit.h"

ProjectionEdit::ProjectionEdit(cv::MorphShapes kerShape,uint kerWidth, uint kerHeigth):kernelShape(kerShape),kernelWidth(kerWidth),kernelHeight(kerHeigth){}
void ProjectionEdit::edit(std::vector<cv::Mat> &projections){
     //photo editing
     cv::Mat kernel= cv::getStructuringElement(kernelShape,cv::Size(kernelWidth,kernelHeight)); //bez upsampling stosowalem 6,6  //po upsampling 3,3
     ///Canny( vecMat, vecMat, 100, 200);
     std::vector<int> compression_params;
     compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
     compression_params.push_back(100);
     //store image in memory buffer (no need to write to file)
     std::vector<uchar> buf;
     //UWAGA - wynik klasyfikacji nieznacznie sie rozni w zaleznosci od zastosowania ponizej jedenj z 3 operacji:
     //1. Zakodowanie (z domyslnymi parametrami czyli m.in. CV_IMWRITE_JPEG_QUALITY=0.95)  orginalnej powyzszej