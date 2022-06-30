#include "src/controller/pointCloudController.h"


PointCloudController::PointCloudController()
{
    boundingBox= std::make_shared<AxisAlignedBoudningBox>();
    visualization= std::make_shared<VisualizationWithBB>(boundingBox);
    objectFactory= std::make_shared<CloudObjectFactory>();
    sceneFactory=std::make_shared<CloudSceneFactory>();
    saveLoad = std::make_shared<SaveLoad>();
    saveLoad->setFactories(this->sceneFactory,this->objectFactory);
}
void PointCloudController::registerQTreeWidgetObserver(QTreeWidget *treeWiOb){
    this->treeWidgetObserver=treeWiOb;
}
void PointCloudController::registerQVTKidgetObserver(QVTKWidget *qVTKWiOb){
    this->qVTKWidgetObserver=qVTKWiOb;
}
void PointCloudController::registerPCLViewerObserver(pcl::visualization::PCLVisualizer::Ptr viewOb){
    this->viewerObserver=viewOb;
}
QTreeWidgetItem* PointCloudController::getTopLevelItem(QTreeWidgetItem* item){
    while(item->parent()!=nullptr){
        item=item->parent();
    }
    return item;
}
/**
 * @brief CloudScenesObservable::getTopLevelIndexOfSelectedCloud
 * @param cloudPath
 * @return Index of selected cloud in treeWidget or of parent (top level) of