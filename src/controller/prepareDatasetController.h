#ifndef PREPAREDATASETCONTROLLER_H
#define PREPAREDATASETCONTROLLER_H
#include <QTreeWidget>
#include <src/model/prepareDataset.h>
class PrepareDatasetController
{
private:
    QTreeWidget* treeWidget=nullptr;
    const int srcPathColumn=0;
    const int dstPathColumn=1;
    const int finishedIndicatorColumn=2;
public:
    PrepareDatasetController(QTreeWidget* trWid);
    void