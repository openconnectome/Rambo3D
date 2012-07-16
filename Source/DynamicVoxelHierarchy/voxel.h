#ifndef VOXEL_H
#define VOXEL_H

//** This object represent the voxel data that will be used for the project.
//** Voxels can be requested, found, and returned in order to be displayed.
class Voxel
{
    char* ID;
    int ResolutionX;
    int ResolutionY;
    int ResolutionZ;

    char* Data;

public:
    Voxel();
    Voxel(char* ID, int ResolutionX, int ResolutionY, int ResolutionZ, char* Data);

};

#endif // VOXEL_H
