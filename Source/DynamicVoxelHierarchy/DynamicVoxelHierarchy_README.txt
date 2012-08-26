Dynamic Voxel Cache and Display
Juneki Hong (jhong29@jhu.edu)


External libraries that I used developing this project:
- LRU Cache library using Boost (https://patrickaudley.com/code/project/lrucache)
   This library was a generic LRU cache that I used. It requires the Boost libraries to run. (http://www.boost.org/)
- HDF5 (http://www.hdfgroup.org/HDF5/)
   The server we request data from uses HDF5. So in order to parse HDF5 files, it needs to be installed on the system.




OVERVIEW OF THE PROJECT
----------------------------------------------------------------------------------------------
I intend to accomplish the dynamic voxel cache in 3 main steps.
1. Determine the voxels that we need given the viewing plane. (VoxelOracle.cpp)
2. Look to see if the data required is available in the cache. (CacheMaintain.cpp)
      Otherwise, make a requests for it.
      And if possible, return a lower resolution version of the data.
3. Take the data provided to us from the cache and render it. (HierarchyRenderer.cpp)

Each step will request information from the previous step in order to function correctly.
----------------------------------------------------------------------------------------------

