
#include "src/view/configuration.h"

Configuration::Configuration(QMainWindow* mW)
{
    this->mainWindow=mW;
}
void Configuration::addWidget(QWidget* widget){
    this->widgets.push_back(widget);
}

void Configuration::addAllWidgetsOfGivenTypes(QList<QWidgetType> widgetTypes){
    for(auto type:widgetTypes){
        switch (type) {
        case 0:
        {
            QList<QSpinBox *> allSpinBox = this->mainWindow->findChildren<QSpinBox *>();
            std::for_each(allSpinBox.begin(),allSpinBox.end(),[&](QSpinBox* x) { addWidget(x); }); //# lambdaexpression: this:&Configuration::addWidget didnt work more info:https://stackoverflow.com/questions/12058603/how-to-use-stdfor-each-on-a-member-function
            break;
        }
        case 1:
        {
            QList<QDoubleSpinBox *> allDoubleSpinBox = this->mainWindow->findChildren<QDoubleSpinBox *>();
            std::for_each(allDoubleSpinBox.begin(),allDoubleSpinBox.end(),[&](QDoubleSpinBox* x) { addWidget(x); });
            break;
        }
        case 2:
        {
            QList<QLineEdit *> allLineEdit = this->mainWindow->findChildren<QLineEdit *>();
            std::for_each(allLineEdit.begin(),allLineEdit.end(),[&](QLineEdit* x) { addWidget(x); });
            break;
        }
        case 3:
        {
            QList<QCheckBox *> allCheckBox = this->mainWindow->findChildren<QCheckBox *>();
            std::for_each(allCheckBox.begin(),allCheckBox.end(),[&](QCheckBox* x) { addWidget(x); });
            break;
        }
        case 4:
        {
            QList<QComboBox *> allComboBox = this->mainWindow->findChildren<QComboBox *>();
            std::for_each(allComboBox.begin(),allComboBox.end(),[&](QComboBox* x) { addWidget(x); });
            break;
        }
        case 5:
        {
            QList<QGroupBox *> allGroupBox = this->mainWindow->findChildren<QGroupBox *>();
            std::for_each(allGroupBox.begin(),allGroupBox.end(),[&](QGroupBox* x) { addWidget(x); });
            break;
        }
        }
    }
}
std::unique_ptr<QWidgetConfigurationAdapter> Configuration::wrap(QWidget *qWidget){
    //determin to witch derived class of QWidget belongs passed argument: (https://stackoverflow.com/questions/43994584/what-is-qobject-cast)
    QSpinBox* qSpinBox=qobject_cast<QSpinBox *>(qWidget);
    if( qSpinBox != nullptr ){
        std::unique_ptr<QSpinBoxConfigurationAdapter> qSpinBoxAdapter=std::make_unique<QSpinBoxConfigurationAdapter>(qSpinBox);
        return std::move(qSpinBoxAdapter);
    }

    QDoubleSpinBox *qDoubleSpinBox=qobject_cast<QDoubleSpinBox *>(qWidget);
    if(qDoubleSpinBox!= nullptr){
        std::unique_ptr<QDoubleSpinBoxConfigurationAdapter> qDoubleSpinBoxAdapter=std::make_unique<QDoubleSpinBoxConfigurationAdapter>(qDoubleSpinBox);
        return std::move(qDoubleSpinBoxAdapter);
    }

    QLineEdit *qLineEdit=qobject_cast<QLineEdit *>(qWidget);
    if(qLineEdit!= nullptr){
        std::unique_ptr<QLineEditConfigurationAdapter> qLineEditAdapter=std::make_unique<QLineEditConfigurationAdapter>(qLineEdit);
        return std::move(qLineEditAdapter);
    }

    QCheckBox *qCheckBox=qobject_cast<QCheckBox *>(qWidget);
    if(qCheckBox!= nullptr){
        std::unique_ptr<QCheckBoxConfigurationAdapter> qCheckBoxAdapter=std::make_unique<QCheckBoxConfigurationAdapter>(qCheckBox);
        return std::move(qCheckBoxAdapter);
    }
    QComboBox *qComboBox=qobject_cast<QComboBox *>(qWidget);
    if(qComboBox!= nullptr){
        std::unique_ptr<QComboBoxConfigurationAdapter> qComboBoxAdapter=std::make_unique<QComboBoxConfigurationAdapter>(qComboBox);
        return std::move(qComboBoxAdapter);
    }
    QGroupBox *qGroupBox=qobject_cast<QGroupBox *>(qWidget);
    if(qGroupBox!= nullptr){
        std::unique_ptr<QGroupBoxConfigurationAdapter> qGroupBoxAdapter=std::make_unique<QGroupBoxConfigurationAdapter>(qGroupBox);
        return std::move(qGroupBoxAdapter);
    }
    //if none of the above
    std::unique_ptr<QWidgetConfigurationAdapter> qWidgetDefaultAdapter=std::make_unique<QWidgetConfigurationAdapter>();
    return std::move(qWidgetDefaultAdapter);

}
    /////
    //QFile file(path);
    //file.open(QIODevice::WriteOnly);
    //QDataStream out(&file);   // we will serialize the data into the file
    //out << QString(data);

bool Configuration::saveConfiguration(QString path){
    std::unique_ptr<QWidgetConfigurationAdapter> adapter;
    QString data="";
    QString name="no_name_set";
    QStringList lineSeen={};
    QFile file(path);

    if (file.open(QIODevice::WriteOnly| QIODevice::Truncate)) {
        QTextStream stream(&file);
        for(auto widget:this->widgets){
            //we could skip writing widget name, but with widget names file can be read seperatly more clearly
            name=widget->objectName();
            /**
             * @brief if(lineSeen.contains(name)){continue;} - dont save duplicated names:
             * QObject::findChildren function returns all children of widgets. It includes also some strange names as:
             * 'qt_spinbox_lineedit'. So one widget, lets say mySpin_QSpinBox has also child 'qt_spinbox_lineedit'. So when we want
             * to save configuration from two widget types (QSpinBox and QLineEdit) we also save name and value for this 'qt_spinbox_lineedit'
             * and because each spin box has this child with the same name, we can unintenionaly assign wrong value to widgets during loading
             * configuration.
             * Assuming widgets named by us (or automatically named in designer) have all unique names, we can get rid of above problem
             * removing (not saving) all repeated names in list returned form findChildren -> this way we will get rid of unwanted chidlren (for ex."qt_spinbox_lineedit")
             * and avoid wrong configuration loading
             */
            if(lineSeen.contains(name)){continue;}
            lineSeen.push_back(name);

            adapter= wrap(widget);

            data=adapter->getConfigurationData();
            stream <<name<<" "<< data << endl;
        }

        file.close();
        qDebug()<<"CONFIGURATION SAVED";
        return true;
    }else {
        qDebug()<<"COULD NOT OPEN "<<path<<" for WRITNING data from widgets";
        return false;
    }
}
//returns index of search widget or -1 if widget with given name is not found
int Configuration::findWidgetWithName(QString widgetName){
    QStringList widgetsNames={};
    int index=-1;
    for(auto widget:widgets){
        widgetsNames.push_back(widget->objectName());
    }
    index=widgetsNames.indexOf(widgetName);
    return index;
}
void Configuration::clear(){
    std::unique_ptr<QWidgetConfigurationAdapter> adapter;
    for(auto widget:widgets){
        adapter= wrap(widget);
        adapter->clearData();
    }
}
bool Configuration::loadConfiguration(QString path){
    std::unique_ptr<QWidgetConfigurationAdapter> adapter;
    QFile file(path);
    QString data="";
    QStringList singleLineWords={};
    int index=-1;

    clear();
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream stream(&file);
        //We are using searching by name so in case of change made in vector of widgets types we want to save, added new widgets to application and so on
        //it takes more time but it assures that configurations are always compatible and can be always loaded (as long as there are widgets (with names form configuration) in application)
        while(!stream.atEnd()){
            data=stream.readLine();
            singleLineWords=data.split(QRegExp(" "));
            index=findWidgetWithName(singleLineWords.at(0));
            //if widget name form configuration file is found among widgets in application
            if(index!=-1){
                adapter=wrap(widgets.at(index));
                adapter->setConfigurationData(singleLineWords.at(1));// values are in second column
            }else{
                qDebug()<<"WIDGET FROM CONFIGURATION FILE '"<<singleLineWords.at(0)<<"' NOT FOUND IN APPLICATION OR THIS TYPE OF WIDGET IS CURRENTLY NOT SET FOR SAVING DATA FROM IT";
            }
        }

        file.close();
        qDebug()<<"CONFIGURATION LOADED";
        return true;
    }else{
        qDebug()<<"COULD NOT OPEN "<<path<<" for READING data from widgets";
    }
}
////////////////////////
QWidgetConfigurationAdapter::QWidgetConfigurationAdapter(){}
QString QWidgetConfigurationAdapter::getConfigurationData(){
    return "default_data";
}
void QWidgetConfigurationAdapter::setConfigurationData(QString value){
}

QSpinBoxConfigurationAdapter::QSpinBoxConfigurationAdapter(QSpinBox* qSpBo):qSpinBox(qSpBo){}
QString QSpinBoxConfigurationAdapter::getConfigurationData(){
    return QVariant(qSpinBox->value()).toString();
}
void QSpinBoxConfigurationAdapter::setConfigurationData(QString value){
    this->qSpinBox->setValue(QVariant(value).toInt());
}
QDoubleSpinBoxConfigurationAdapter::QDoubleSpinBoxConfigurationAdapter(QDoubleSpinBox* qDoSpBo):qDoubleSpinBox(qDoSpBo){}
QString QDoubleSpinBoxConfigurationAdapter::getConfigurationData(){
    return QVariant(qDoubleSpinBox->value()).toString();
}
void QDoubleSpinBoxConfigurationAdapter::setConfigurationData(QString value){
    this->qDoubleSpinBox->setValue(QVariant(value).toDouble());
}
QLineEditConfigurationAdapter::QLineEditConfigurationAdapter(QLineEdit* qLiEd):qLineEdit(qLiEd){}
QString QLineEditConfigurationAdapter::getConfigurationData(){
    return QVariant(qLineEdit->text()).toString();
}
void QLineEditConfigurationAdapter::setConfigurationData(QString value){
    this->qLineEdit->setText(value);
}
QCheckBoxConfigurationAdapter::QCheckBoxConfigurationAdapter(QCheckBox* qChBo):qCheckBox(qChBo){}
QString QCheckBoxConfigurationAdapter::getConfigurationData(){
    return QVariant(this->qCheckBox->isChecked()).toString();
}
void QCheckBoxConfigurationAdapter::setConfigurationData(QString value){
    this->qCheckBox->setChecked(QVariant(value).toBool());
}
QComboBoxConfigurationAdapter::QComboBoxConfigurationAdapter(QComboBox* qCoBo):qComboBox(qCoBo){}
QString QComboBoxConfigurationAdapter::getConfigurationData(){
    return QVariant(this->qComboBox->currentIndex()).toString();
}
void QComboBoxConfigurationAdapter::setConfigurationData(QString value){
    this->qComboBox->setCurrentIndex(QVariant(value).toInt());
}
QGroupBoxConfigurationAdapter::QGroupBoxConfigurationAdapter(QGroupBox* qGrBo):qGroupBox(qGrBo){}
QString QGroupBoxConfigurationAdapter::getConfigurationData(){
    return QVariant(this->qGroupBox->isChecked()).toString();
}
void QGroupBoxConfigurationAdapter::setConfigurationData(QString value){
    this->qGroupBox->setChecked(QVariant(value).toBool());
}