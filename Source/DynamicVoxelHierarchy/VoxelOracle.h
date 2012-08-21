#ifndef VOXELORACLE_H
#define VOXELORACLE_H

#include "geometry.h"
#include "voxel.h"
#include <vector>
#include <list>
#include <string>


const bool MANUAL_CONTROL = true;


class VoxelOracle
{
    int zoomedIn;
    Plane3D viewingPlane;

    std::vector<Voxel> manualControl;

public:
    VoxelOracle();


    VoxelOracle(int zoomedIn, Plane3D viewingPlane);

    //** Sets the viewing plane to whatever is specified
    void setViewingPlane(Point3D normal = Point3D(), Point3D point = Point3D());

    //** Sets how much we are zoomed in.
    void setZoomedIn(int zoom=0);

    int getZoomedIn();

    //** Based on how zoomed in we are, we determine the maximum resolution required to display
    int determineResolution();

    //** Given a viewing plane, this function will return a list of all of the voxel data required to render.
    std::vector<Voxel> determineVoxelsNeeded();

    void setManualControl(std::vector<Voxel> l);

};

#endif // VOXELORACLE_H
