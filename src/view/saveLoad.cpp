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
 * @brief S