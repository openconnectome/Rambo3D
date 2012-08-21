#include "VoxelOracle.h"
#include "geometry.h"

//** Default Constructor
VoxelOracle::VoxelOracle()
{
    zoomedIn = 0;
    viewingPlane = Plane3D();

    manualControl = std::vector<Voxel>();
    manualControl.clear();
    manualControl.push_back(Voxel("A"));
}



//** Constructor
VoxelOracle::VoxelOracle(int zoomedIn, Plane3D viewingPlane)
{
    this->zoomedIn = zoomedIn;
    this->viewingPlane = viewingPlane;

    manualControl = std::vector<Voxel>();
    manualControl.clear();
    manualControl.push_back(Voxel("A"));
}

//** Sets how much we are zoomed in.
void VoxelOracle::setZoomedIn(int zoom)
{
    zoomedIn = zoom;
}

int VoxelOracle::getZoomedIn()
{
    return zoomedIn;
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

    if(MANUAL_CONTROL)
    {
        return manualControl;
    }

    std::vector<Voxel> list = std::vector<Voxel>();

    //Dummy code
    string ID = "a";
    string ID2 = "b";

    Voxel v = Voxel(ID,zoomedIn);
    Voxel v2 = Voxel(ID2,zoomedIn);

    list.clear();
    list.push_back(v);
    list.push_back(v2);

    printf("VoxelOracle returns a list of size: %d\n", list.size());
    return list;
}




void VoxelOracle::setManualControl(std::vector<Voxel> l)
{
    manualControl = l;
}




