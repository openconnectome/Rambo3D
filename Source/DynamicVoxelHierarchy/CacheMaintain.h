#ifndef CACHEMAINTAIN_H
#define CACHEMAINTAIN_H

#include "voxel.h"
//#include "voxelDatabase.h"
#include "timer.h"

// HDF5. The server that we request data from uses HDF5
#include <H5Cpp.h>
using namespace H5;


#include <string>
#include <vector>
#include <list>

/*
The implementation for a cache object was taken from:
http://patrickaudley.com/code/project/lrucache
*/
#include "DynamicVoxelHierarchy/lru_cache/src/lru_cache.h"

typedef std::string string;

class CacheMaintain
{

public:

    int cacheCapacity;
    int hierarchySize;

    typedef LRUCache<std::string,Voxel> cacheType;
    std::vector<cacheType*> cacheHierarchy;

 //   voxelDatabase database;

    void test();

    //** Constructors
    CacheMaintain();
    CacheMaintain(int cacheCapacity,int hierarchySize);

    //** Gets the Voxel data. First checks to see if it exists in the cache. Requests it if it doesnt.
    Voxel getVoxelData(string ID, int resolution=0);

    //** Requests a voxel. The request could go to the harddrive or across the network.
    Voxel requestVoxel(string ID);

    //** We check to see if the voxel is in our cache hierarchy
    bool isInCache(string ID);
    bool isInCache(string ID, int resolution);

    void printCache();

    void insertVoxelData(string ID, Voxel v, int resolution);

private:
     void setCache();

};

#endif // CACHEMAINTAIN_H
