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
    while(*it){
        //# qDebug()<<"CHILD DATA-id is null?="<<(*it)->data(0, Qt::UserRole).isNull();
        //# qDebug()<<"CHILD DATA-id="<<(*it)->data(0, Qt::UserRole).toInt();
        //iterate over parent children that have given id
        if(!(*it)->data(0, Qt::UserRole).isNull() && (*it)->parent()==parent && (*it)->data(0, Qt::UserRole).toInt()==id){
            return *it;
        }
        ++it;
    }
    return nullptr;
}
void PointCloudController::clearViewer(pcl::visualization::PCLVisualizer::Ptr viewer){
    viewer->removeAllPointClouds();
    viewer->removeAllShapes();
}
void PointCloudController::clearTreeWidgetTreeChildren(){
    QTreeWidgetItemIterator it(this->treeWidgetObserver,QTreeWidgetItemIterator::HasChildren); //iterate only over items that have children
      while (*it) {
          //we only clear objects on the top level
          if((*it)->parent()!=nullptr)
          {
              qDebug()<<"CHILDREN SKIPPING";
              continue;
          }
          (*it)->takeChildren();
          ++it;
      }
}
std::size_t PointCloudController::getMemoryUsageOfCachedClouds(){
    std::size_t total_size=0;
    for(auto const &cloud:cachedClouds){
        //updateTreeWidgetItem(cloud->getSourcePath(),cloud->getCloudsNames());
        total_size=total_size+cloud->getCloudSize();
    }
    return total_size;
}
void PointCloudController::setCachedCloudsMemoryLimit(std::size_t limit){
    this->cachedCloudsMemoryLimit=limit;
}
/**
 * @brief PointCloudController::updateView
 * updates whole view
 */
void PointCloudController::updateView(){
    clearTreeWidgetTreeChildren();
    for(auto const &cloud:cachedClouds){
        //updateTreeWidgetItem(cloud->getSourcePath(),cloud->getCloudsNames());
        cloud->updateView();
    }
    qDebug()<<"TOTAL MEMORY USAGE BY CLOUDS[MB]="<<static_cast<float>(getMemoryUsageOfCachedClouds())/static_cast<float>(1000000);
}
/**
 * @brief PointCloudController::updateView
 * @param cloud
 * Updates only one item in view that referes to particular cloud
 */
void PointCloudController::updateView(CloudComponent *cloud){
    updateTreeWidgetItem(cloud);
}
/**
 * @brief PointCloudController::updateView
 * @param cloud
 * Updates only one selected item in view
 */
void PointCloudController::updateView(QTreeWidgetItem* item){
    int topLevelCloudIndex;
    std::string cloudPath="";
    topLevelCloudIndex=getTopLevelIndexOfSelectedCloud(item);
    //item=getTopLevelItem(item);
    //cloudPath=item->text(0).toStdString();

    //# UWAGA - tu przekazuje raw ptr (pobrany z unique_ptr  -> ptr.get()), bo taki akceptuje ponizsza funkcja- powinienem tak robic tylko
    //# wtedy, gdy jestem pewny ze obiekt wskazywany przez unique_ptr bedzie caly czas istnial w trakcie wykonywania ponizszej funkcji :https://stackoverflow.com/questions/30905487/how-can-i-pass-stdunique-ptr-into-a-function
    try {
     