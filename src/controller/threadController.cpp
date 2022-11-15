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
void Worker::benchmark(const cloudControllerSharedPtr modelController, listOfTreeWidgetItemRawPtr selectedClouds,benchmarkTypeSharedPtr benchmarkType, stdString folderPath){
    QString result="BENCHMARK FINISHED";
    modelController->benchmark(selectedClouds,benchmarkType,folderPath);
    //qDebug()<<"BENCHMARK thread:  "<<thread()->currentThreadId();
    emit resultReady(result);
}
void Worker::prepareFrom3D(const prepareDatasetControllerSharedPtr controller, prepareDatasetFrom3DSharedPtr prepareDatasetFrom3D){
    QString result="PREPARING DATA FROM 3D OBJECTS FINISHED";
    controller->prepare(prepareDatasetFrom3D);
    emit resultReady(result);
}
void Worker::extractObjectsInstances(const prepareDatasetControllerSharedPtr controller,extractObjectsInstancesSharedPtr extractObjectsInstances){
    QString result="EXTRACTING SINGLE INSTANCES FROM SCENES WITH OBJECTS BELONGING TO SAME CLASSES FINISHED";
    controller->extract(extra