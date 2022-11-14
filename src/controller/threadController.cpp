#include "src/controller/threadController.h"
/* stara wersja classify
void Worker::classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,classificationTypeSharedPtr classificationType,stdString modelPath,integer numOfClasses){
    QString result="CLASSIFICATION FINISHED";
    //qDebug()<<"CLASSIFICATION thread:  "<<thread()->currentThreadId();
    modelController->classify(selectedClouds,classificationType,modelPath,numOfClasses);
    emit resultReady(result);
}
*/
void Worker::classify(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds
              ,classificationTypeSharedPtr classificationType,segmentationTypeSharedPtr segmentationType
              ,projectionTypeSharedPtr projectionType, editTypeSharedPtr editType
                      ,stdString modelPath,integer numOfClasses){
    QString result="CLASSIFICATION FINISHED";
    //qDebug()<<"CLASSIFICATION thread:  "<<thread()->currentThreadId();
    modelController->classify(selectedClouds,classificationType,segmentationType,projectionType,editType,modelPath,numOfClasses);
    emit resultReady(result);
}
void Worker::b