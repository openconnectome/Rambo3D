#include "voxel.h"

#define GL_GLEXT_PROTOTYPES 1
#include <GL/glu.h>

#include <QtOpenGL>
#include <qapplication.h>



Voxel::Voxel()
{

}


Voxel::Voxel(char* ImagePath , char* AnnotationPath , int ResX , int ResY , int ResZ)
{
    imgPath = ImagePath;
    anoPath = AnnotationPath;

    resX = ResX;
    resY = ResY;
    resZ = ResZ;


}



void Voxel::loadTextureFromURL( char* imagePath , int resX , int resY , int resZ , GLuint& ID )
{
    QFile file( imagePath );
    file.open( QFile::ReadOnly );
    uchar *memory = file.map( 0 , file.size() );
    glEnable( GL_TEXTURE_3D );
    glGenTextures( 1 , &ID );
    glBindTexture( GL_TEXTURE_3D , ID );
    glPixelStorei( GL_UNPACK_ALIGNMENT , 1 );
    glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );
    glTexParameteri( GL_TEXTURE_3D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
    glTexParameteri( GL_TEXTURE_3D , GL_TEXTURE_MIN_FILTER , GL_LINEAR );
    glTexParameteri( GL_TEXTURE_3D , GL_TEXTURE_WRAP_S , GL_REPEAT );
    glTexParameteri( GL_TEXTURE_3D , GL_TEXTURE_WRAP_T , GL_REPEAT );
    glTexParameteri( GL_TEXTURE_3D , GL_TEXTURE_WRAP_R , GL_REPEAT );
    glTexImage3D(
                    GL_TEXTURE_3D,	// target
                    0,			// level
                    GL_LUMINANCE ,      // internal format
                    resX,resY,resZ,     // width, height, depth
                    0,			// border,
                    GL_LUMINANCE ,      // input format
                    GL_UNSIGNED_BYTE,	// type
                    memory		// GLvoid* pixels
                );
    file.unmap( memory );
}



