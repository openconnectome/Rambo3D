#include "HierarchyRenderer.h"

#include <iostream>
#include <fstream>
#include <string>


using std::string;
using std::ifstream;
using std::cout;
using std::endl;


HierarchyRenderer::HierarchyRenderer()
{
    VoxelOracle *newOracle = new VoxelOracle();
    CacheMaintain *newCache = new CacheMaintain();
    this->oracle = newOracle;
    this->cache = newCache;
}

HierarchyRenderer::HierarchyRenderer(VoxelOracle* oracle, CacheMaintain* cache)
{
    this->oracle = oracle;
    this->cache = cache;
}

//** Gets the VoxelOracle object
VoxelOracle* HierarchyRenderer::getOracle()
{
    return oracle;
}

//** Gets the CacheMaintain object
CacheMaintain* HierarchyRenderer::getCache()
{
    return cache;
}


//** Will render one voxel on the screen
void HierarchyRenderer::render(Voxel v)
{
    v = Voxel();
}

//** Uses the voxelOracle and the cache to figure out and render the correct voxels on the screen
void HierarchyRenderer::renderDynamicVoxels()
{
    std::vector<Voxel> VoxelsNeeded = oracle->determineVoxelsNeeded();
    int size = VoxelsNeeded.size();

    int i =0;
    for(i = 0; i < size; i++)
    {
        Voxel v = VoxelsNeeded.at(i);

        string ID = v.getID();
        cout << "Looking for Voxel ID: " << ID << endl;
        int resolution = v.getResolution();

        Voxel v2 = cache->getVoxelData(ID,resolution);

        render(v2);
    }
}
