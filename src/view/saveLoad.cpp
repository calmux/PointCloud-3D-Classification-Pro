#include "src/view/saveLoad.h"

SaveLoad::SaveLoad()
{
    setSeparator(";");
}
void SaveLoad::setFactories(std::shared_ptr<CloudSceneFactory> scnFac,std::shared_ptr<CloudObjectFactory> objFac){
    this->sceneFactory=scnFac;
    this->objectFactory=objFac;
}
bool SaveLoad::saveTXT(QString path,const std::vector