#include "src/controller/pointCloudController.h"


PointCloudController::PointCloudController()
{
    boundingBox= std::make_shared<AxisAlignedBoudningBox>();
    visualization= std::make_shared<VisualizationWithBB>(boundingBox);
    objectFactory= std