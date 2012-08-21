#ifndef HIERARCHYRENDERER_H
#define HIERARCHYRENDERER_H

#include "VoxelOracle.h"
#include "CacheMaintain.h"

class HierarchyRenderer
{
    VoxelOracle* oracle;
    CacheMaintain* cache;

public:
//    HierarchyRenderer(VoxelOracle oracle = VoxelOracle(), CacheMaintain cache = CacheMaintain());
    HierarchyRenderer();
    HierarchyRenderer(VoxelOracle* oracle, CacheMaintain* cache);

    //** Gets the VoxelOracle object
    VoxelOracle* getOracle();

    //** Gets the CacheMaintain object
    CacheMaintain* getCache();

    //** Will render one voxel on the screen
    void render(Voxel v);

    //** Uses the voxelOracle and the cache to figure out and render the correct voxels on the screen
    void renderDynamicVoxels();


};

#endif // HIERARCHYRENDERER_H
