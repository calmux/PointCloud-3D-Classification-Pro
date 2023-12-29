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