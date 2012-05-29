#ifndef CAMERA_INCLUDED
#define CAMERA_INCLUDED
#include <stdio.h>
#include "geometry.h"
/** This class stores information about the camera. */
class RayCamera {
public:
        //ming
        Matrix3D RodRotationFormula( const Point3D& axis , const float& angle );

        /** The field of view of the camera */
        double heightAngle;
        /** The aspect ratio of the view plane */
        double aspectRatio;
        /** The position of the camera in world coordinates */
        Point3D position;
        /** The direction that the camera is looking */
        Point3D direction;
        /** The up direction of the camera */
        Point3D up;
        /** The right direction of the camera */
        Point3D right;

        /** This method reads in the camera information from a .ray file.*/
        int read(FILE* fp);
        /** This method writes out the camera information to a .ray file. If no file is specified,
          * the camera is written out to stdout. */
        void write(FILE* fp=stdout);

        /** This method calls the OpenGL commands for setting up the camera. */
        void drawOpenGL(void);

        /** This call rotates the camera, about the axis which is parallel to the up direction of the camera, and passes
          * through the specified point. */
        void rotateUp(Point3D center,float angle);
        /** This call rotates the camera, about the axis which is parallel to the right direction of the camera, and passes
          * through the specified point. */
        void rotateRight(Point3D center,float angle);

        //ming
        void rotateDir( Point3D center , float angle );

        /** This call moves the camera in the forward direction by the specified distance.*/
        void moveForward(float dist);
        /** This call moves the camera in the right direction by the specified distance.*/
        void moveRight(float dist);
        /** This call moves the camera in the up direction by the specified distance.*/
        void moveUp(float dist);
};
#endif // CAMERA_INCLUDED


