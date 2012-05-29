#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#define MISHA_CODE 1
#define DEFAULT_WIN_WIDTH  800
#define DEFAULT_WIN_HEIGHT 800
#define DEFAULT_FOV 50.0
#include <qgl.h>
#include <QHash>
#include <time.h>
#include "glCamera.h"
#include "geometry.h"

class QGLShaderProgram;
class QGLShader;
class QTimer;

class ControlPanel : public QGLWidget
{
        Q_OBJECT
public:
        ControlPanel( char* ImagePath , char* AnnotationPath , int ResX , int ResY , int ResZ , int timerInterval=33, QWidget *parent=0, char *name=0 );
        QSize minimumSizeHint()const { return QSize( 500               , 500                ); }
        QSize sizeHint()       const { return QSize( DEFAULT_WIN_WIDTH , DEFAULT_WIN_HEIGHT ); }

        char* imgPath;
        char* anoPath;

        RayCamera camera;
        void setProjection( int width , int height , bool orthoProj );
        bool OrthoProj;
        bool isShiftDown;
        double orthoProjSize;

        bool isDrawing; // the zooming windwos
        Point2D drawStart , drawEnd;

        std::vector< bool > visibility;
        bool allVisible;
        bool drawViewBBox;
        bool localCoordinate;
        bool drawTails;

        GLuint imgID , anoID;
        Plane3D viewPlane;
        int resX , resY , resZ;
        int overlay;
        float sliceSpacing;
        float gamma;
        float initialBlendingScale;
        float blendingScaleMultiplier;

        BoundingBox3D viewBBox;
        BoundingBox3D globalBBox;

        int currentWidth;
        int currentHeight;

        bool doneUpdate;

        int sliceNumber;

        void grabOrhoView( QImage &imageXY , QImage &imageYZ , QImage &imageZX );
        void paintGL();
        void loadTextureFromURL         ( char* imagePath , int resX , int resY , int resZ , GLuint& ID );
        void loadTextureFromURL_addColor( char* imagePath , int resX , int resY , int resZ , GLuint& ID );

        void keyPressEvent  ( QKeyEvent *event );
        void keyReleaseEvent( QKeyEvent *event );

protected:
        void loadTextureFromFile();
        void initializeGL();
        void resizeGL( int width, int height );
        //void paintGL();
        //void keyPressEvent  ( QKeyEvent *event );
        //void keyReleaseEvent( QKeyEvent *event );
        void mousePressEvent    (   QMouseEvent *event );
        void mouseMoveEvent     (   QMouseEvent *event );
        void mouseReleaseEvent  (   QMouseEvent *event );
        void wheelEvent         (   QWheelEvent *event );
        void timeOut();

        void getIntersections( std::vector< Point3D >& iPoints );
        void drawBox( Point3D min , Point3D max );

protected slots:
        virtual void timeOutSlot();

private:
        QTimer *m_timer;
        QPoint lastPos;

        float planeDistance;
        Point3D planeNormal;
        Point3D planeUp;
        Point3D planeRight;

        QGLShaderProgram *ShaderProgram;
        QGLShader *VertexShader, *FragmentShader;

signals:
    void clicked();

public slots:
    void slotSetGamma           ( int input );
    void slotSetInitialScale    ( int input );
    void slotSetScaleMultiplier ( int input );
    void slotSetSliceSpacing    ( int input );


//
// testing GLSL shaders...
//
public:
    //void render_buffer_to_screen( GLuint ID );
    //void loadFake3DTexture( GLuint &ID );
    //void loadFake2DTexture( GLuint &ID );
    void loadFakeTexture( GLuint &ID );
    void LoadShader(QString vshader, QString fshader);
    bool isUsingShader;
private:
    GLint texloc;
    GLint volume_texloc;
    GLuint backface_buffer , temp_buffer[2];
    GLuint framebuffer;
    GLuint fake2Dtexture;
};

#endif
