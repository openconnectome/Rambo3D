
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glu.h>


//#include <GL/glew.h>
#include <QtOpenGL>
#include <qapplication.h>
#include <qtimer.h>
#include <QKeyEvent>
#include <QImageReader>
#include <qimage.h>
#include <cfloat>

#include "ControlPanel.h"
#include "glCamera.h"

void ControlPanel::keyReleaseEvent( QKeyEvent *event )
{
}
void ControlPanel::keyPressEvent( QKeyEvent *event )
{
}

ControlPanel::ControlPanel( char* ImagePath , char* AnnotationPath , int ResX , int ResY , int ResZ , int timerInterval, QWidget *parent, char *name ) : QGLWidget( parent )
{
        this->imgPath = ImagePath;
        this->anoPath = AnnotationPath;
        this->resX = ResX;
        this->resY = ResY;
        this->resZ = ResZ;

        if( timerInterval == 0 ) m_timer = 0;
        else
        {
                m_timer = new QTimer( this );
                connect( m_timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()) );
                m_timer->start( timerInterval );
        }
        planeDistance=0.0;
        planeRight  = Point3D(1,0,0);
        planeUp     = Point3D(0,1,0);
        planeNormal = Point3D(0,0,1);

        OrthoProj = false;
        viewPlane = Plane3D( Point3D(0,0,1) , Point3D( 0.5 , 0.5 , 0.5/this->resZ + 0.5 ) );

        overlay = 0;
        sliceSpacing = 1;
        gamma = 1.0;
        initialBlendingScale = 0.3;
        blendingScaleMultiplier = 0.3;

        orthoProjSize = 0.51;
        drawTails = true;

        isUsingShader = false;
}

void ControlPanel::mousePressEvent( QMouseEvent *event )
{
        lastPos = event->pos();
        if( ( event->button() & Qt::RightButton ) && !isShiftDown )
        {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT , viewport );
            isDrawing = true;
            drawStart = drawEnd = Point2D( event->posF().x() / viewport[2] , 1.0 - event->posF().y()/viewport[3] );
        }
        //emit clicked();
}

void ControlPanel::mouseReleaseEvent( QMouseEvent *event )
{
        lastPos = event->pos();
        if( ( event->button() & Qt::RightButton ) && !isShiftDown )
        {
            GLint viewport[4];
            glGetIntegerv(GL_VIEWPORT , viewport );
            isDrawing = false;
            drawEnd =  Point2D( event->posF().x() / viewport[2] , 1.0 - event->posF().y()/viewport[3] );

            Point2D center = ( drawEnd + drawStart );
            double halfHeight = tan( DEFAULT_FOV / 360 * PI );
            double halfWidth  = halfHeight * viewport[2] / viewport[3];
            Point3D rayDirection = camera.direction  +  camera.up * halfHeight * (center[1]-1)  +  camera.right * halfWidth * (center[0]-1);
            rayDirection = rayDirection.unit();
            double t = ( viewPlane.distance - viewPlane.normal.dot(camera.position) ) / viewPlane.normal.dot(rayDirection);
            Point3D intersection = camera.position + rayDirection * t;
            double halfDiagonal = ( drawEnd - drawStart ).length() / 2;
            camera.position = intersection - camera.direction * (halfDiagonal/halfHeight*1.1);
        }
        emit clicked();
}

void ControlPanel::wheelEvent(QWheelEvent *event)
{
        if( isShiftDown )
        {
            if( !doneUpdate ) return;
            else doneUpdate = false;
            if(event->delta()>0) viewPlane.position += viewPlane.normal * ( 1.0 / resZ );
            else                 viewPlane.position -= viewPlane.normal * ( 1.0 / resZ );
            viewPlane.distance = viewPlane.normal.dot( viewPlane.position );

            if(event->delta()>0) sliceNumber++;
            else                 sliceNumber--;
        }
        else
        {
            camera.moveForward( event->delta()*0.001 );
            if( OrthoProj )
            {
                if(event->delta()>0) orthoProjSize+=0.1;
                else                 orthoProjSize-=0.1;
                setProjection( currentWidth , currentHeight , true );
            }
        }
        emit clicked();
}

void ControlPanel::mouseMoveEvent( QMouseEvent *event )
{
        QPoint shift = event->pos() - lastPos;
        lastPos = event->pos();

        if( event->buttons() & Qt::MiddleButton )
        {
            camera.rotateUp   ( Point3D(.5,.5,.5) , 0.01*shift.x() );
            camera.rotateRight( Point3D(.5,.5,.5) , 0.01*shift.y() );
        }
        else if( event->buttons() & Qt::LeftButton )
        {
            if( isShiftDown )
            {
                Point3D pos = viewPlane.position - camera.up*(float(shift.y())*0.003) + camera.right*(float(shift.x())*0.003);
                pos += viewPlane.normal * ( viewPlane.distance - pos.dot((viewPlane.normal)) );
                viewPlane = Plane3D( viewPlane.normal , pos );
            }
            else
            {
                camera.moveRight( -float(shift.x())*0.002 );
                camera.moveUp   ( float(shift.y())*0.002 );
            }
        }
        else if( event->buttons() & Qt::RightButton )
        {
            if( isShiftDown )
            {
               viewPlane.normal = camera.RodRotationFormula( camera.up    , 0.01*shift.x() ) * viewPlane.normal;
               viewPlane.normal = camera.RodRotationFormula( camera.right , 0.01*shift.y() ) * viewPlane.normal;
               viewPlane = Plane3D( viewPlane.normal , viewPlane.position );
            }
            else
            {
                GLint viewport[4];
                glGetIntegerv(GL_VIEWPORT , viewport );
                drawEnd = Point2D( event->posF().x() / viewport[2] , 1.0 - event->posF().y()/viewport[3] );
            }
        }
}

void ControlPanel::timeOut()
{
    paintGL();
    updateGL();
    doneUpdate = true;
}

void ControlPanel::timeOutSlot()
{
    timeOut();
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: loadTextureFromURL()
// Goal:
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::loadTextureFromURL( char* imagePath , int resX , int resY , int resZ , GLuint& ID )
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

void ControlPanel::loadTextureFromURL_addColor( char* imagePath , int resX , int resY , int resZ , GLuint& ID )
{
    QFile file( imagePath );
    file.open( QFile::ReadOnly );

    uchar *memory = file.map( 0 , file.size() );
    float* data = new float[ file.size()*3 ];

    static time_t timeSeed = time(NULL);
    for( int i=0 ; i<resX*resY*resZ ; i++ )
    {
        if( memory[i]==uchar(0) )
        {
            data[i*3  ] = 0.;
            data[i*3+1] = 0.;
            data[i*3+2] = 0.;
        }
        else
        if( memory[i]==uchar(255) )
        {
            data[i*3  ] = 0.;
            data[i*3+1] = 1.;
            data[i*3+2] = 1.;
        }
        else
        {
            srand( memory[i]* timeSeed );
            data[i*3  ] = double(rand())/RAND_MAX;
            data[i*3+1] = double(rand())/RAND_MAX;
            data[i*3+2] = double(rand())/RAND_MAX;
        }
    }

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
                    GL_RGB ,            // internal format
                    resX,resY,resZ,     // width, height, depth
                    0,			// border,
                    GL_RGB ,            // input format
                    GL_FLOAT,           // type
                    data		// GLvoid* pixels
                );
    file.unmap( memory );
    delete data;
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: initializeGL()
// Goal: Initialization
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::initializeGL()
{
    //glewInit();

    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);

    glDisable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    camera.position     = Point3D( 0.5f , 0.5f , 2.7f );
    camera.direction    = Point3D( 0.0f , 0.0f ,-1.0f );
    camera.up           = Point3D( 0.0f , 1.0f , 0.0f );
    camera.right        = Point3D( 1.0f , 0.0f , 0.0f );

    loadTextureFromURL         ( imgPath , resX , resY , resZ , imgID );
    loadTextureFromURL_addColor( anoPath , resX , resY , resZ , anoID );

    ShaderProgram = NULL;
    VertexShader = FragmentShader = NULL;
    LoadShader("./vertexShader.vs", "./fragmentShader.fs");
    glUseProgram(0);

    // Create the to FBO's one for the backside of the volumecube and one for the finalimage rendering
    glGenFramebuffersEXT(1, &framebuffer);
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,framebuffer);

    glGenTextures(1, &backface_buffer);
    glBindTexture(GL_TEXTURE_2D, backface_buffer);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, 741, 764, 0, GL_RGBA, GL_FLOAT, NULL);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, backface_buffer, 0);

    {
        glGenTextures(1, &temp_buffer[0]);
        glBindTexture(GL_TEXTURE_2D, temp_buffer[0]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, 741, 764, 0, GL_RGBA, GL_FLOAT, NULL);

                GLfloat *memory = new GLfloat[741*764*4];
                for( int i=0 ; i<741*764 ; i++ )
                {
                    memory[i*4+0] = 0.1;
                    memory[i*4+1] = 0.7;
                    memory[i*4+2] = 0.3;
                    memory[i*4+3] = 1.0;
                }
                glEnable( GL_TEXTURE_2D );
                glBindTexture( GL_TEXTURE_2D , temp_buffer[0] );
                glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA16F_ARB , 741 , 764 , 0 , GL_RGBA , GL_FLOAT , memory );
                delete memory;
    }

    {
        glGenTextures(1, &temp_buffer[1]);
        glBindTexture(GL_TEXTURE_2D, temp_buffer[1]);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
        glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA16F_ARB, 741, 764, 0, GL_RGBA, GL_FLOAT, NULL);

                GLfloat *memory = new GLfloat[741*764*4];
                for( int i=0 ; i<741*764 ; i++ )
                {
                    memory[i*4+0] = 0.1;
                    memory[i*4+1] = 0.7;
                    memory[i*4+2] = 0.3;
                    memory[i*4+3] = 1.0;
                }
                glEnable( GL_TEXTURE_2D );
                glBindTexture( GL_TEXTURE_2D , temp_buffer[1] );
                glTexImage2D( GL_TEXTURE_2D , 0 , GL_RGBA16F_ARB , 741 , 764 , 0 , GL_RGBA , GL_FLOAT , memory );
                delete memory;
    }

    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT , 0 );
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: setProjection()
// Goal: set up the camera projection
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::setProjection( int width , int height , bool orthoProj )
{
    currentWidth = width;
    currentHeight = height;
    OrthoProj   = orthoProj;
    double aRatio = double(width) / height;
    if(orthoProj) aRatio=1; //!!!???

    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( OrthoProj ) glOrtho( -orthoProjSize*aRatio , orthoProjSize*aRatio , -orthoProjSize , orthoProjSize , -5 , 5 );
    else            gluPerspective( DEFAULT_FOV , (GLfloat)width/(GLfloat)height , FLT_MIN , 100.0f );
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: resizeGL()
// Goal: Resize
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::resizeGL( int width , int height)
{
    setProjection( width , height , OrthoProj );
    printf( "resizeGL( %d , %d )\n" , width , height );
    emit clicked();
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: getIntersections()
// Goal: computer the points where the viewPlane and the unit grid meets
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::getIntersections( std::vector< Point3D >& iPoints )
{
    static std::vector< Ray3D > rays;
    static bool hasInvoked = false;

    if( !hasInvoked )
    {
        float min = 0.0 - FLT_MIN;
        float max = 1.0 + FLT_MIN;
        rays.push_back( Ray3D( Point3D(min,min,min) , Point3D( 1, 0, 0 ) ) );
        rays.push_back( Ray3D( Point3D(min,min,min) , Point3D( 0, 1, 0 ) ) );
        rays.push_back( Ray3D( Point3D(max,max,min) , Point3D(-1, 0, 0 ) ) );
        rays.push_back( Ray3D( Point3D(max,max,min) , Point3D( 0,-1, 0 ) ) );
        rays.push_back( Ray3D( Point3D(min,min,max) , Point3D( 1, 0, 0 ) ) );
        rays.push_back( Ray3D( Point3D(min,min,max) , Point3D( 0, 1, 0 ) ) );
        rays.push_back( Ray3D( Point3D(max,max,max) , Point3D(-1, 0, 0 ) ) );
        rays.push_back( Ray3D( Point3D(max,max,max) , Point3D( 0,-1, 0 ) ) );
        rays.push_back( Ray3D( Point3D(min,min,min) , Point3D( 0, 0, 1 ) ) );
        rays.push_back( Ray3D( Point3D(min,max,min) , Point3D( 0, 0, 1 ) ) );
        rays.push_back( Ray3D( Point3D(max,min,min) , Point3D( 0, 0, 1 ) ) );
        rays.push_back( Ray3D( Point3D(max,max,min) , Point3D( 0, 0, 1 ) ) );
        hasInvoked = true;
    }

    iPoints.clear();
    for( size_t i=0 ; i<rays.size() ; i++ )
    {
        Point3D temp;
        float t;
        if(  rays[i].intersect( viewPlane , temp , t )  &&  t>0  &&  t<1  )
            iPoints.push_back( temp );
    }

    Point3D center;
    for( size_t i=0 ; i<iPoints.size() ; i++ ){ center += iPoints[i]; }
    center /= iPoints.size();

    std::vector< float > angles;
    int orient;
    if( fabs(viewPlane.normal[0])>0.00001 ) orient=0;
    if( fabs(viewPlane.normal[1])>0.00001 ) orient=1;
    if( fabs(viewPlane.normal[2])>0.00001 ) orient=2;
    for( size_t i=0 ; i<iPoints.size() ; i++ )
    {
        Point3D diff = iPoints[i] - center;
        angles.push_back( atan2( diff[(orient+2)%3] , diff[(orient+1)%3] ) );
    }

    for( size_t i=0 ; i<iPoints.size() ; i++ )
        for( size_t j=0 ; j<iPoints.size()-i-1 ; j++ )
            if( angles[j] >  angles[j+1] )
            {
                float tempA = angles[j];
                angles[j] = angles[j+1];
                angles[j+1] = tempA;
                Point3D tempP = iPoints[j];
                iPoints[j] = iPoints[j+1];
                iPoints[j+1] = tempP;
            }
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: drawBox()
// Goal: Drawing a Box
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::drawBox( Point3D min , Point3D max )
{
    glDisable(GL_LINE_STIPPLE);
    glPolygonMode( GL_FRONT , GL_POINT );
    glPolygonMode( GL_BACK  , GL_LINE  );
    glBegin( GL_QUADS );
        glVertex3f( max[0],max[1],max[2] );    glVertex3f( min[0],max[1],max[2] );    glVertex3f( min[0],min[1],max[2] );    glVertex3f( max[0],min[1],max[2] );
        glVertex3f( max[0],min[1],min[2] );    glVertex3f( min[0],min[1],min[2] );    glVertex3f( min[0],max[1],min[2] );    glVertex3f( max[0],max[1],min[2] );
        glVertex3f( max[0],max[1],max[2] );    glVertex3f( max[0],min[1],max[2] );    glVertex3f( max[0],min[1],min[2] );    glVertex3f( max[0],max[1],min[2] );
        glVertex3f( min[0],max[1],min[2] );    glVertex3f( min[0],min[1],min[2] );    glVertex3f( min[0],min[1],max[2] );    glVertex3f( min[0],max[1],max[2] );
        glVertex3f( max[0],max[1],min[2] );    glVertex3f( min[0],max[1],min[2] );    glVertex3f( min[0],max[1],max[2] );    glVertex3f( max[0],max[1],max[2] );
        glVertex3f( max[0],min[1],max[2] );    glVertex3f( min[0],min[1],max[2] );    glVertex3f( min[0],min[1],min[2] );    glVertex3f( max[0],min[1],min[2] );
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: paintOrhoTexture()
// Goal:
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::grabOrhoView( QImage &imageXY , QImage &imageYZ , QImage &imageZX )
{
    RayCamera cam = camera;
    Plane3D plane = viewPlane;
    int oldWidth = currentWidth;
    int oldHeight = currentHeight;
    bool wasOrtho = OrthoProj;
    double oldOrthoProjSize = orthoProjSize;

    orthoProjSize = 0.51;
    setProjection( currentWidth , currentHeight , true );
    camera.position  = Point3D( 0.5f , 0.5f , 0.5f );

        camera.direction = Point3D(0,0,-1);
        camera.up        = Point3D(0,1,0);
        camera.right     = Point3D(1,0,0);
        viewPlane = Plane3D( Point3D(0,0,1) , viewPlane.position );
        paintGL();
        imageXY = grabFrameBuffer();

        camera.direction = Point3D(-1,0,0);
        camera.up        = Point3D(0,1,0);
        camera.right     = Point3D(0,0,-1);
        viewPlane = Plane3D( Point3D(1,0,0) , viewPlane.position );
        paintGL();
        imageYZ = grabFrameBuffer();

        camera.direction = Point3D(0,-1,0);
        camera.up        = Point3D(0,0,-1);
        camera.right     = Point3D(1,0,0);
        viewPlane = Plane3D( Point3D(0,-1,0) , viewPlane.position );
        paintGL();
        imageZX = grabFrameBuffer();

    viewPlane = plane;
    camera    = cam;
    orthoProjSize = oldOrthoProjSize;
    setProjection( oldWidth , oldHeight , wasOrtho );
}


////////////////////////////////////////////////////////////////////////////////////////
// Function: LoadShader()
// Goal: loading the custom vertex/fragment shaders
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::LoadShader( QString vshader , QString fshader )
{
    if(ShaderProgram)
        {
        ShaderProgram->release();
        ShaderProgram->removeAllShaders();
        }
    else ShaderProgram = new QGLShaderProgram;

    if(VertexShader)
        {
        delete VertexShader;
        VertexShader = NULL;
        }

    if(FragmentShader)
        {
        delete FragmentShader;
        FragmentShader = NULL;
        }

    // load and compile vertex shader
    QFileInfo vsh(vshader);
    if(vsh.exists())
        {
        VertexShader = new QGLShader(QGLShader::Vertex);
        if(VertexShader->compileSourceFile(vshader))
            ShaderProgram->addShader(VertexShader);
        else qWarning() << "Vertex Shader Error" << VertexShader->log();
        }
    else qWarning() << "Vertex Shader source file " << vshader << " not found.";


    // load and compile fragment shader
    QFileInfo fsh(fshader);
    if(fsh.exists())
        {
        FragmentShader = new QGLShader(QGLShader::Fragment);
        if(FragmentShader->compileSourceFile(fshader))
            ShaderProgram->addShader(FragmentShader);
        else qWarning() << "Fragment Shader Error" << FragmentShader->log();
        }
    else qWarning() << "Fragment Shader source file " << fshader << " not found.";

    //
    // Shader Program
    //
    if(!ShaderProgram->link())
        {
        qWarning() << "Shader Program Linker Error" << ShaderProgram->log();
        }
    else ShaderProgram->bind();
    texloc        = glGetUniformLocation(ShaderProgram->programId(), "tex");
    volume_texloc = glGetUniformLocation(ShaderProgram->programId(), "volume_tex");
}

inline void vertex(float x, float y, float z)
{
        glColor3f(x,y,z);
        glMultiTexCoord3fARB(GL_TEXTURE1_ARB, x, y, z);
        glVertex3f(x,y,z);
}
// this method is used to draw the front and backside of the volume
inline void drawQuads(float x, float y, float z)
{
    glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
    glBegin(GL_QUADS);
        glNormal3f( 0.0, 0.0,-1.0); vertex(0.0, 0.0, 0.0); vertex(0.0, y  , 0.0); vertex(  x, y  , 0.0); vertex(x  , 0.0, 0.0);
        glNormal3f( 0.0, 0.0, 1.0); vertex(0.0, 0.0, z  ); vertex(x  , 0.0, z  ); vertex(  x, y  , z  ); vertex(0.0, y  , z  );
        glNormal3f( 0.0, 1.0, 0.0); vertex(0.0, y  , 0.0); vertex(0.0, y  , z  ); vertex(  x, y  , z  ); vertex(x  , y  , 0.0);
        glNormal3f( 0.0,-1.0, 0.0); vertex(0.0, 0.0, 0.0); vertex(x  , 0.0, 0.0); vertex(  x, 0.0, z  ); vertex(0.0, 0.0, z  );
        glNormal3f(-1.0, 0.0, 0.0); vertex(0.0, 0.0, 0.0); vertex(0.0, 0.0, z  ); vertex(0.0, y  , z  ); vertex(0.0, y  , 0.0);
        glNormal3f( 1.0, 0.0, 0.0); vertex(x  , 0.0, 0.0); vertex(x  , y  , 0.0); vertex(  x, y  , z  ); vertex(x  , 0.0, z  );
    glEnd();
}

////////////////////////////////////////////////////////////////////////////////////////
// Function: paintGL()
// Goal: Drawing
////////////////////////////////////////////////////////////////////////////////////////
void ControlPanel::paintGL()
{
    if( isUsingShader )
    {
        glUseProgram(0);
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT , framebuffer );
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, backface_buffer, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        camera.drawOpenGL();

        glEnable(GL_CULL_FACE);
        glCullFace(GL_FRONT);
        drawQuads(1.0,1.0, 1.0);
        glDisable(GL_CULL_FACE);

        glUseProgram( ShaderProgram->programId() );
        //glBindFramebufferEXT( GL_FRAMEBUFFER_EXT , framebuffer );
        glBindFramebufferEXT( GL_FRAMEBUFFER_EXT , 0 );
        //glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, temp_buffer[0], 0);
        glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        camera.drawOpenGL();

        glActiveTexture(GL_TEXTURE1);
        glEnable(GL_TEXTURE_3D);
        glBindTexture(GL_TEXTURE_3D, anoID );
        glUniform1i(volume_texloc, 1);

        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, backface_buffer);
        glUniform1i(texloc, 0);

        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
        drawQuads(1.0,1.0, 1.0);
        glDisable(GL_CULL_FACE);

        glActiveTexture(GL_TEXTURE1);
        glDisable(GL_TEXTURE_3D);
        glActiveTexture(GL_TEXTURE0);
        glDisable(GL_TEXTURE_2D);

        glUseProgram( 0 );

        // Draw the Bounding Boxes
        glDisable( GL_TEXTURE_2D);
        glLineWidth( 3 );
        glColor3f( 0.0f , 1.0f , 1.0f );
        drawBox( Point3D(0,0,0) , Point3D(1,1,1) );
        if( drawViewBBox )
        {
            glLineWidth(1);
            drawBox( viewBBox.p[0] , viewBBox.p[1]  );
        }

        return;
    }

    glUseProgram(0);
    glBindFramebufferEXT( GL_FRAMEBUFFER_EXT , 0 );
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, 0, 0);
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    camera.drawOpenGL();

    std::vector< Point3D > iPoints;
    getIntersections( iPoints );

    glEnable ( GL_BLEND      );
    glEnable ( GL_TEXTURE_3D );
    glDisable( GL_DEPTH_TEST );
    glTexEnvi( GL_TEXTURE_ENV , GL_TEXTURE_ENV_MODE , GL_MODULATE );

    glBlendEquation( GL_ADD );
    glColor4f( 1.0f , 1.0f , 1.0f , 0.5 * gamma );
    glBlendFunc( GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA );

        //
        // Render the annotation
        //
        glBindTexture( GL_TEXTURE_3D , anoID );
        glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
        glColor4f( 0.5f , 0.3f , 0.9f , 1.0 );
        glBlendFunc( GL_SRC_ALPHA , GL_ONE );
            //glBlendFunc( GL_CONSTANT_ALPHA , GL_ONE );
            //glBlendColor( 0 , 0 , 0 , scale * gamma );
        glBegin( GL_POLYGON );
            for( int i=0 ; i<int(iPoints.size()) ; i++)
            {
                glTexCoord3f( iPoints[i][0] , iPoints[i][1] , iPoints[i][2] );
                glVertex3f  ( iPoints[i][0] , iPoints[i][1] , iPoints[i][2] );
            }
        glEnd();
        //
        // Render the image
        //
        glBindTexture( GL_TEXTURE_3D , imgID );
        glPolygonMode( GL_FRONT_AND_BACK , GL_FILL );
        glColor4f( 1.f , 1.f , 1.f , 0.5 );
        glBlendFunc( GL_SRC_ALPHA , GL_ONE );
        glBegin( GL_POLYGON );
            for( int i=0 ; i<int(iPoints.size()) ; i++)
            {
                glTexCoord3f( iPoints[i][0] , iPoints[i][1] , iPoints[i][2] );
                glVertex3f  ( iPoints[i][0] , iPoints[i][1] , iPoints[i][2] );
            }
        glEnd();


    glDisable( GL_BLEND      );
    glDisable( GL_TEXTURE_3D );
    glEnable ( GL_DEPTH_TEST );

    //Draw the outline
    glLineWidth( 5 );
    glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );
    glColor3f( 1 , 1 , 0 );
    glBegin( GL_LINE_LOOP );
        for( int i=0 ; i<int(iPoints.size()) ; i++) glVertex3f  ( iPoints[i][0] , iPoints[i][1] , iPoints[i][2] );
    glEnd();

/*
    // Draw axes
    glLineWidth(3);
    glBegin(GL_LINES);
        glColor3f( 1.0f , 0.0f , 0.0f );    glVertex3f( 0.0f , 0.0f , 0.0f );  glVertex3f( 5.0f , 0.0f , 0.0f );
        glColor3f( 0.0f , 1.0f , 0.0f );    glVertex3f( 0.0f , 0.0f , 0.0f );  glVertex3f( 0.0f , 5.0f , 0.0f );
        glColor3f( 0.0f , 0.0f , 1.0f );    glVertex3f( 0.0f , 0.0f , 0.0f );  glVertex3f( 0.0f , 0.0f , 5.0f );
    glEnd();
*/
    // Draw the Bounding Boxes
    glLineWidth( 3 );
    glColor3f( 0.0f , 1.0f , 1.0f );
    drawBox( Point3D(0,0,0) , Point3D(1,1,1) );
    if( drawViewBBox )
    {
        glLineWidth(1);
        drawBox( viewBBox.p[0] , viewBBox.p[1]  );
    }

    // Draw the handle
    Point3D offset = viewPlane.normal * 0.1;
    static GLUquadric* quad = gluNewQuadric();
    glPushMatrix();
        glPushMatrix();
            glTranslatef( .5 , .5 , .5 );
            glColor3f( 1.0f , 0.0f , 0.0f );
            gluSphere( quad , .01 , 10 , 10  );
        glPopMatrix();
        glTranslatef( viewPlane.position.p[0] , viewPlane.position.p[1] , viewPlane.position.p[2] );
        glColor3f( 1.0f , 0.3f , 0.6f );
        gluSphere( quad , .01 , 10 , 10  );

        glLineWidth(2);
        glBegin(GL_LINES);
            glVertex3f(0,0,0);
            glVertex3f( offset.p[0] , offset.p[1] , offset.p[2] );
        glEnd();
        glPushMatrix();
            glTranslatef( offset.p[0] , offset.p[1] , offset.p[2] );
            glColor3f( 0.3f , 0.5f , 1.0f );
            gluSphere( quad , .01 , 10 , 10  );
        glPopMatrix();
    glPopMatrix();

    GLint viewport[4];
    glGetIntegerv( GL_VIEWPORT , viewport );
    double aspectRatio = double( viewport[3] ) / viewport[2];
    glMatrixMode( GL_PROJECTION );
    glPushMatrix();
        glLoadIdentity();
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
            glLoadIdentity();
            glTranslatef( -1 , -1 , -1 );
            glScalef( 2 , 2 , 2 );
            glColor3f( 1 , 1 , 1 );
            glLineWidth( 3.0 );
            glBegin( GL_LINES );
                glVertex2f( 0.49 , 0.5 );
                glVertex2f( 0.51 , 0.5 );
                glVertex2f( 0.5 , 0.5 - 0.01/aspectRatio );
                glVertex2f( 0.5 , 0.5 + 0.01/aspectRatio );
            glEnd();
            if( isDrawing ) // the zooming window
            {
                glPolygonMode( GL_FRONT_AND_BACK , GL_LINE );
                glLineWidth( 3.0 );
                glBegin( GL_QUADS );
                    glVertex2f( drawStart[0] , drawStart[1] );
                    glVertex2f( drawEnd[0]   , drawStart[1] );
                    glVertex2f( drawEnd[0]   , drawEnd[1]   );
                    glVertex2f( drawStart[0] , drawEnd[1]   );
                glEnd();
                glLineWidth( 1.0 );
                glBegin( GL_LINES );
                    Point2D center = ( drawStart + drawEnd ) / 2;
                    double size = std::min( fabs(drawStart[0]-drawEnd[0]) , fabs(drawStart[1]-drawEnd[1]) ) * 0.1;
                    glVertex2f( center[0] - size , center[1] );
                    glVertex2f( center[0] + size , center[1] );
                    glVertex2f( center[0] , center[1] - size/aspectRatio );
                    glVertex2f( center[0] , center[1] + size/aspectRatio );
                glEnd();
            }
        glPopMatrix();
        glMatrixMode( GL_PROJECTION );
    glPopMatrix();

    static bool hasDrawn=false;
    if( !hasDrawn )
    {
        hasDrawn=true;
        emit clicked();
    }
}
