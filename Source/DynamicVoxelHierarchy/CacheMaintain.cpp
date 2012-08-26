#include "CacheMaintain.h"

#include <iostream>
#include <fstream>
#include <string>


using std::string;
using std::ifstream;
using std::cout;
using std::endl;



//** Default constructor
CacheMaintain::CacheMaintain()
{
    cacheCapacity = 10;
    hierarchySize = 10;
    setCache();

//    database = voxelDatabase();
}

//** Constructor
CacheMaintain::CacheMaintain(int cacheCapacity, int hierarchySize)
{
    this->cacheCapacity = cacheCapacity;
    this->hierarchySize = hierarchySize;
    setCache();

//    database = voxelDatabase();
}

//** Instantiates the cache object
void CacheMaintain::setCache()
{
//    cache = new cacheType(cacheCapacity);
    cacheHierarchy = std::vector<cacheType*>(hierarchySize);

    for(int i=0; i<hierarchySize; i++)
    {
        cacheType *newCache = new cacheType(cacheCapacity);

//        string temp = "foo";
//        newCache->insert(temp,Voxel());

        cacheHierarchy[i] = newCache;
    }

    cacheType* testCache = cacheHierarchy.at(0);

}

//** Just a small test making sure the Cache works. I keep this here to try out small things.
void CacheMaintain::test()
{
    std::string one = "test";
    Voxel v = Voxel();

    /*
    cache->insert(one,v);
    cache->fetch("test").printData();

    cache->clear();

    */
}


//** Given a requested voxel, we make a request for the voxel and return the same voxel filled with data.
Voxel CacheMaintain::getVoxelData(string ID, int resolution)
{
    int i = resolution;

    for(i;i<hierarchySize;i++)
    {
        //printf("i: %d\n",i);
        //printf("hierarchySize: %d\n",hierarchySize);

        // iterate and check each cache that we have sequentially
        cacheType* tempCache = cacheHierarchy[i];

        if(tempCache->exists(ID))
        {
            //Just checking the rest of the hierarchy. Update to make sure it stays.
            int j = i+1;
            for(j; j<hierarchySize;j++)
            {
                cacheType* remainingCache = cacheHierarchy[j];
                remainingCache->touch(ID);
            }


            printf("Cache level: %d, Success. Cache hit.\n\n",i);
            return *(tempCache->fetch_ptr(ID));
        }
        else
        {
            printf("Cache level: %d, Cache miss.\n",i);
            Voxel v = requestVoxel(ID);
            tempCache->insert(ID,v);
        }
    }

    // At this point, we checked all of our caches and we did not find it.

    printf("\n");
    return Voxel();
}

//** Makes a request for the voxel (either across the network or read off of the hard drive)
Voxel CacheMaintain::requestVoxel(string ID)
{
    //TODO

    timer clock =  timer();
    clock.setTime();

    printf("Requesting Voxel...");
    //Voxel v = database.getFile(ID);


    for(int i = 0; i<100000000; i++)
    {
        if(i % 1000000000 == 0 && i > 0)
        {
            printf("AAAAAA: %d\n",i);
        }
    }


    time_t elapsed = clock.timeElapsed();
    printf("%ld seconds elapsed \n",elapsed);

    return Voxel(ID);
//    return v;
}


//** Checks if the voxel exists in our cache hierarchy
bool CacheMaintain::isInCache(string ID)
{
    int resolution = 0;
    for(resolution=0; resolution<hierarchySize; resolution++)
    {
        cacheType* temp = cacheHierarchy[resolution];
        if(temp->exists(ID))
            return true;
    }
    return false;
}

//** Checks if the voxel exists in our cache hierarchy at a particular resolution
bool CacheMaintain::isInCache(string ID, int resolution)
{
    cacheType* tempCache = cacheHierarchy[resolution];
    return tempCache->exists(ID);
}



void CacheMaintain::printCache()
{
    int i = 0;
    for(i=0;i<hierarchySize;i++)
    {
        cout << i<< ": ";
        cacheType* tempCache = cacheHierarchy[i];

        std::vector<string> keyList = tempCache->get_all_keys();

        int j = 0;
        for(j=0;j<keyList.size();j++)
        {
            string tempKey = keyList[j];
            cout<< tempKey << ", ";
        }
        cout << endl;
    }
}


void CacheMaintain::insertVoxelData(string ID, Voxel v, int resolution)
{
    cacheType* tempCache = cacheHierarchy[resolution];
    tempCache->insert(ID,v);
}


