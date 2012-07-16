#ifndef HIERARCHYRENDERER_H
#define HIERARCHYRENDERER_H

#include "VoxelOracle.h"
#include "CacheMaintain.h"

class HierarchyRenderer
{
    VoxelOracle oracle;
    CacheMaintain cache;

public:
    HierarchyRenderer(VoxelOracle oracle = VoxelOracle(), CacheMaintain cache = CacheMaintain());

    void renderDynamicVoxels();
    void render(Voxel v);
};

#endif // HIERARCHYRENDERER_H
