#include <math.h>

#include <GL/glu.h>
#include <qgl.h>
#include <qapplication.h>


#include <QtOpenGL>
#include "glCamera.h"

Matrix3D RayCamera::RodRotationFormula( const Point3D& axis , const float& angle )
{
    double C=cos(angle), S=sin(angle);
    float x = axis.p[0], y = axis.p[1], z = axis.p[2];

    Matrix3D rotation = Matrix3D();

    rotation.m[0][0]= 1+ (1-C)*(x*x-1);
    rotation.m[0][1]= (z*S) + (1-C)*x*y;
    rotation.m[0][2]= (-y*S) + (1-C)*x*z;

    rotation.m[1][0]= (-z*S)+(1-C)*x*y;
    rotation.m[1][1]= 1 + (1-C)*(y*y-1);
    rotation.m[1][2]= (x*S) + (1-C)*y*z;

    rotation.m[2][0]= (y*S) + (1-C)*x*z;
    rotation.m[2][1]= (-x*S) + (1-C)*y*z;
    rotation.m[2][2]= 1+(1-C)*(z*z-1);

    return rotation;
}

//////////////////
// OpenGL stuff //
//////////////////

void RayCamera::drawOpenGL(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(position[0],              position[1],              position[2],
              position[0]+direction[0], position[1]+direction[1], position[2]+direction[2],
              up[0],              	up[1],		          up[2]                    );
}

void RayCamera::rotateUp( Point3D center , float angle )
{
    Matrix3D rotation = RodRotationFormula( up , -angle );
    position = position - center;
    position = rotation * position;
    position = position + center;
    direction = ( rotation * direction ).unit();
    right     = ( rotation * right ).unit();
}

void RayCamera::rotateRight( Point3D center , float angle )
{
    Matrix3D rotation = RodRotationFormula( right , -angle );
    position = position - center;
    position = rotation * position;
    position = position + center;
    direction = rotation * direction;
    up        = rotation * up;
}


void RayCamera::rotateDir( Point3D center , float angle )
{
    Matrix3D rotation = RodRotationFormula( direction , -angle );
    position = position - center;
    position = rotation * position;
    position = position + center;
    right    = ( rotation * right ).unit();
    up       = ( rotation * up ).unit();
}

void RayCamera::moveForward(float dist)
{
        position += direction*dist;
}

void RayCamera::moveRight(float dist)
{
        position += right*dist;
}

void RayCamera::moveUp(float dist)
{
        position += up*dist;
}

