#include "HierarchyRenderer.h"



HierarchyRenderer::HierarchyRenderer(VoxelOracle oracle, CacheMaintain cache)
{
    this->oracle = oracle;
    this->cache = cache;
}

void HierarchyRenderer::render(Voxel v)
{

}


void HierarchyRenderer::renderDynamicVoxels()
{
    std::vector<Voxel> VoxelsNeeded = oracle.determineVoxelsNeeded();

    for(uint i=0; i < VoxelsNeeded.size(); i++)
    {
        Voxel v = VoxelsNeeded[i];

        if(cache.isInCache(v))
        {
            v = cache.getFromCache(v);
        }
        else
        {
            v = Voxel();
        }

        render(v);
    }
}

