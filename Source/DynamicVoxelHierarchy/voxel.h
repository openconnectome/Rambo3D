#ifndef VOXEL_H
#define VOXEL_H

#include <stdio.h>
#include <string>

using std::string;

//#include <qgl.h>

//** This object represent the voxel data that will be used for the project.
//** Voxels can be requested, found, and returned in order to be displayed.
class Voxel
{
    string ID;
    int Resolution;

//    char* dataLocation;
//    FILE* Data;

public:
    Voxel();
    Voxel(string ID, int Resolution=0);
//    Voxel(string ID, int ResolutionX, int ResolutionY, int ResolutionZ, char* dataLocation);
//    Voxel(string ID, int Resolution, char* dataLocation);

    void printData();
    string getID();
    int getResolution();

};

#endif // VOXEL_H
