#ifndef CACHEMAINTAIN_H
#define CACHEMAINTAIN_H

#include "voxel.h"

class CacheMaintain
{
public:
    CacheMaintain();

    //** Given a requested voxel, we make a request for the voxel and return the same voxel filled with data.
    Voxel getVoxelData(Voxel v);

    //** Similar function to getVoxelData. We could probably merge the two functions together.
    Voxel requestVoxel(Voxel v);

    //** We check to see if the voxel is in our cache hierarchy
    Voxel getFromCache(Voxel v);
    bool isInCache(Voxel v);

};

#endif // CACHEMAINTAIN_H
