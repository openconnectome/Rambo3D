#include "CacheMaintain.h"

//** Default constructor
CacheMaintain::CacheMaintain()
{
    cacheCapacity = 10;
    setCache();

    test();
}

//** Constructor
CacheMaintain::CacheMaintain(int size)
{
    cacheCapacity = size;
    setCache();
}

//** Just a small test making sure the Cache works. I keep this here to try out small things.
void CacheMaintain::test()
{
    std::string one = "test";
    Voxel v = Voxel();

    cache->insert(one,v);
    cache->fetch("test").printData();

    cache->clear();
}




//** Given a requested voxel, we make a request for the voxel and return the same voxel filled with data.
Voxel CacheMaintain::getVoxelData(string ID)
{
    if(isInCache(ID))
    {
        return *(cache->fetch_ptr(ID));
    }
    else
    {
        //TODO: Make a request for it
        Voxel v = requestVoxel(ID);
        cache->insert(ID,v);
        return v;
    }
}

//** Makes a request for the voxel (either across the network or read off of the hard drive)
Voxel CacheMaintain::requestVoxel(string ID)
{
    //TODO
    return Voxel();
}

//** Checks if the voxel exists in our cache hierarchy and tries to retrieve it
Voxel CacheMaintain::getFromCache(string ID)
{
    if(isInCache(ID))
    {
        return *(cache->fetch_ptr(ID));
    }
    else
    {
        return Voxel();
    }

}

//** Checks if the voxel exists in our cache hierarchy
bool CacheMaintain::isInCache(string ID)
{
    return cache->exists(ID);
}



//** Instantiates the cache object
void CacheMaintain::setCache()
{
    cache = new cacheType(cacheCapacity);
}


