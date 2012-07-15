#ifndef VOXELORACLE_H
#define VOXELORACLE_H

#include "geometry.h"
#include "voxel.h"
#include <vector>

class VoxelOracle
{
    int zoomedIn;
    Plane3D viewingPlane;


public:
    VoxelOracle();

    void setViewingPlane(Point3D normal, Point3D point);

    //Given a viewing plane, this function will return a list of all of the voxel data required to render.
    std::vector<Voxel> determineVoxelsNeeded(Plane3D viewingPlane);

};

#endif // VOXELORACLE_H
