#include "VoxelOracle.h"

//** Default Constructor
VoxelOracle::VoxelOracle()
{
    zoomedIn = 0;
    viewingPlane = Plane3D();
}

//** Constructor
VoxelOracle::VoxelOracle(int zoomedIn, Plane3D viewingPlane)
{
    this->zoomedIn = zoomedIn;
    this->viewingPlane = viewingPlane;
}

//** Sets how much we are zoomed in.
void VoxelOracle::setZoomedIn(int zoom)
{
    zoomedIn = zoom;
}

//** Based on how zoomed in we are, we determine the maximum resolution required to display
int VoxelOracle::determineResolution()
{
    //Dummy function. Implement later.
    return zoomedIn;
}

//** Sets the Viewing plane
void VoxelOracle::setViewingPlane(Point3D normal, Point3D point)
{
    viewingPlane = Plane3D(normal, point);
}

//** Given a viewing plane, this function will return a list of all of the voxel data required to render.
std::vector<Voxel> VoxelOracle::determineVoxelsNeeded()
{
    std::vector<Voxel> list = std::vector<Voxel>();

    //Dummy code
    Voxel v = Voxel();
    list.push_back(v);

    return list;
}






