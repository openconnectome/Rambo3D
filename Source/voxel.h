#ifndef VOXEL_H
#define VOXEL_H

#include <qgl.h>


// This object represent the voxel data that will be used for the project.
// Voxels can be requested, found, and returned in order to be displayed.


class Voxel
{

    char* imgPath;
    char* anoPath;

    int resX , resY , resZ;

public:
    Voxel();
    Voxel(char* ImagePath, char* AnnotationPath, int ResX, int ResY, int ResZ);


    void loadTextureFromURL( char* imagePath , int resX , int resY , int resZ , GLuint& ID );




};

#endif // VOXEL_H
