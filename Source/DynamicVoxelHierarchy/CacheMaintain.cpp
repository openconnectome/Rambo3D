#include "CacheMaintain.h"

CacheMaintain::CacheMaintain()
{
}

//** Given a requested voxel, we make a request for the voxel and return the same voxel filled with data.
Voxel CacheMaintain::getVoxelData(Voxel v)
{
    return v;
}

//** Similar function to getVoxelData. We could probably merge the two functions together.
Voxel CacheMaintain::requestVoxel(Voxel v)
{
    return v;
}

//** We check to see if the voxel is in our cache hierarchy
Voxel CacheMaintain::getFromCache(Voxel v)
{
    return v;
}

bool CacheMaintain::isInCache(Voxel v)
{
    return false;
}
