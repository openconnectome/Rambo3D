#ifndef CACHEMAINTAIN_H
#define CACHEMAINTAIN_H

#include "voxel.h"
typedef std::string string;

/*
The implementation for a cache object was taken from:
http://patrickaudley.com/code/project/lrucache
*/
#include "DynamicVoxelHierarchy/lru_cache/src/lru_cache.h"


class CacheMaintain
{

public:

    int cacheCapacity;

    typedef LRUCache<std::string,Voxel> cacheType;
    cacheType *cache;


    void test();

    //** Constructors
    CacheMaintain();
    CacheMaintain(int size);

    //** Given a requested voxel, we make a request for the voxel and return the same voxel filled with data.
    Voxel getVoxelData(string ID);

    //** Similar function to getVoxelData. We could probably merge the two functions together.
    Voxel requestVoxel(string ID);

    //** We check to see if the voxel is in our cache hierarchy
    Voxel getFromCache(string ID);
    bool isInCache(string ID);

private:
     void setCache();

};

#endif // CACHEMAINTAIN_H
