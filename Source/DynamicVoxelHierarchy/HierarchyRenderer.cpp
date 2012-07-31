#include "HierarchyRenderer.h"


HierarchyRenderer::HierarchyRenderer(VoxelOracle oracle, CacheMaintain cache)
{
    this->oracle = oracle;
    this->cache = cache;
}

//** Will render one voxel on the screen
void HierarchyRenderer::render(Voxel v)
{
    v = Voxel();
}

//** Uses the voxelOracle and the cache to figure out and render the correct voxels on the screen
void HierarchyRenderer::renderDynamicVoxels()
{
    std::vector<Voxel> VoxelsNeeded = oracle.determineVoxelsNeeded();

    for(unsigned int i=0; i < VoxelsNeeded.size(); i++)
    {
        Voxel v = VoxelsNeeded[i];
        string ID = v.getID();

        if(cache.isInCache(ID))
        {
            v = cache.getFromCache(ID);
        }
        else
        {
            v = Voxel();
        }

        render(v);
    }
}
