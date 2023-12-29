#include "src/view/saveSettings.h"
#include "ui_saveSettings.h"

SaveSettings::SaveSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveSettings)
{
    ui->setupUi(this);
    saveConditions=std::make_shared<SaveConditions>();
}

SaveSettings::~SaveSettings()
{
    delete ui;
}
QString SaveSettings::getSavePath(){
    return this->savePath;
}
void SaveSettings::on_pushButton_2_clicked()
{
     reject();
}

void SaveSettings::on_save_pushButton_clicked()
{
    savePath=QFileDialog::getExistingDirectory(this,tr("Select clouds save folder"),"/home/");
    if(this->ui->clsIDs_lineEdit->text()!=""){
        addCondition(std::bind(&SaveSettings::isAmongClasses, this, std::placeholders::_1));
    }
    if(this->ui->nnRespon_doubleSpinBox->value()>0){
        addCondition(std::bind(&SaveSettings::hasNnResponseStrengthBiggerEqualThan, this, std::placeholders::_1));
    }
    if(this->ui->cloudSize_spinBox->value()>0){
        addCondition(std::bind(&SaveSettings::hasNumOfPointsBiggerEqualThan, this, std::placeholders::_1));
    }
    if(this->ui->saveParentScene_checkBox->isChecked()){
        this->saveConditions->setSaveParentScene(true);
    }else{
        this->saveConditions->setSaveParentScene(false);
    }
    if(this->savePath!=""){
        accept();
    }else{
        reject();
    }

}
QStringList SaveSettings::getClassesIDs(){
    return this->ui->clsIDs_lineEdit->text().split(classesSeparator,QString::SkipEmptyParts);
}
float SaveSettings::getMinNnResponseSt