#include "voxel.h"

//** Default Constructor
Voxel::Voxel()
{
    char defaultName[] = "Default Name";
    char defaultData[] = "foo";

    ID = defaultName;
    ResolutionX = 512;
    ResolutionY = 512;
    ResolutionZ = 16;
    Data = defaultData;
}

//** Constructor
Voxel:: Voxel(char* ID , int ResolutionX , int ResolutionY , int ResolutionZ , char* Data )
{
    this->ID = ID;
    this->ResolutionX = ResolutionX;
    this->ResolutionY = ResolutionY;
    this->ResolutionZ = ResolutionZ;
    this->Data = Data;
}



