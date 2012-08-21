#ifndef VOXELDATABASE_H
#define VOXELDATABASE_H

#include "voxel.h"
#include <vector>
#include <list>
#include <stdio.h>
#include <iostream>
#include <fstream>


class voxelDatabase
{
    //std::vector<FILE*> inefficientDatabase;



public:
    voxelDatabase();

    void addFile(string ID);
    void addFile(Voxel v);

//    std::string getFile(string ID);
    Voxel getFile(string ID);

    void temp();
};

#endif // VOXELDATABASE_H
