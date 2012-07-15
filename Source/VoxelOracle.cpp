#include "VoxelOracle.h"

VoxelOracle::VoxelOracle()
{
    zoomedIn = 0;
    viewingPlane = Plane3D();
}

void VoxelOracle::setViewingPlane(Point3D normal, Point3D point)
{
    viewingPlane = Plane3D(normal, point);
}

//Given a viewing plane, this function will return a list of all of the voxel data required to render.
std::vector<Voxel> VoxelOracle::determineVoxelsNeeded(Plane3D viewingPlane)
{
    std::vector<Voxel> list = std::vector<Voxel>();

    Voxel v = Voxel();
    //list.insert(v);

    return list;
}


