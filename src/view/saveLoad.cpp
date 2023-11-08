#include "src/view/saveLoad.h"

SaveLoad::SaveLoad()
{
    setSeparator(";");
}
void SaveLoad::setFactories(std::shared_ptr<CloudSceneFactory> scnFac,std::shared_ptr<CloudObjectFactory> objFac){
    this->sceneFactory=scnFac;
    this->objectFactory=objFac;
}
bool SaveLoad::saveTXT(QString path,const std::vector<std::string> saveVector){
    QFile file(path+"/saved.txt");
    if (file.open(QIODevice::WriteOnly| QIODevice::Truncate)) {
        QTextStream stream(&file);
        for(auto &line:saveVector){
            stream <<QString(line.c_str())<<endl;
        }
        file.close();
        qDebug()<<"TXT WITH CLOUD INFO SAVED";
        return true;
    }else {
        qDebug()<<"COULD NOT OPEN "<<path<<" for WRITNING data with CLOUD INFO";
        return false;
    }
}
/**
 * @brief SaveLoad::saveSingleCloud
 * Saves one cloud + creates single line with cloud info (name, sourcePath,class id and so on) and returnes it so it can be saved to file
 * @param cloud
 * @param saveFolderPath
 * @param saveParentScenes
 * @return one line to be saved to file with cloud info
 */
std::string SaveLoad::saveSingleCloud(CloudComponent *cloud,QString saveFolderPath,bool saveParentScenes,std::shared_ptr<SaveConditions> saveCond){
    std::stringstream line("");

    std::string FILEPATH, newParentFILEPATH;

    //children (created for. ex during segmentation) and saved parent scnenes have set sourcePath like this:
    if(ends_with(cloud->getName(),".pcd")){
        FILEPATH=saveFolderPath.toStdString()+"/"+cloud->getName();
    }else{
        FILEPATH=saveFolderPath.toStdString()+"/"+cloud->getName()+".pcd";

    }
    if(cloud->getParentSourcePath()!=""){
        if(ends_with(cloud->getParentSceneName(),".pcd")){
            newParentFI