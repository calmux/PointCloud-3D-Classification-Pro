
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