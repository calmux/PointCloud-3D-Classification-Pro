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
 * @return Index of selected cloud in treeWidget or of parent (top level) of selected cloud (if selected cloud is not in a top level item in a tree widget -> cloud is an object after segmentation)
 */
int PointCloudController::getTopLevelIndexOfSelectedCloud(QTreeWidgetItem* item){
    item=getTopLevelItem(item);
    //index=this->treeWidgetObserver->indexOfTopLevelItem(item); //# tego nie moge uzywac, bo powinieme zwrocic index w vektorze cachedClouds, a nie w hierarchi treeWidget
    //qDebug()<<"INDEX RETURNED FORM QTreeWidget::indexOfTopLevelItem(item)="<<index;
    for(int i=0; i<cachedClouds.size();++i){
        if(cachedClouds.at(i)->getSourcePath()==item->text(0).toStdString())
            return i;
    }
    //we didnt found cloudScene witch such sourcePath
    return -1;
}
QTreeWidgetItem* PointCloudController::getChildItemWithID(QTreeWidgetItem* parent,int id){
    //# TA FUNKCJA NIE DZIALA -> zwraca np. rodzica zamiast dziecko o danym id
    QTreeWidgetItemIterator it(parent);
   