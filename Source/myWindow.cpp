#include <GL/glew.h>
#include <QtOpenGL>
#include <QtGui>
#include "ControlPanel.h"
#include "myWindow.h"

myWindow::myWindow( char* ImagePath , char* AnnoPath , int DataResX , int DataResY , int DataResZ )
{
        QGridLayout *mainLayout = new QGridLayout;

        controlPanel = new ControlPanel( ImagePath , AnnoPath , DataResX , DataResY , DataResZ , 30 );
        connect( controlPanel , SIGNAL(clicked()) , this , SLOT(setCurrentGlWidget()) );
        mainLayout->addWidget( controlPanel , 0 , 0 , 3 , 3 );

        imageLabelXY = new QLabel();
        imageLabelXY->setMaximumHeight( 250 );
        imageLabelXY->setMaximumWidth ( 250 );
        imageLabelXY->setMinimumHeight( 250 );
        imageLabelXY->setMinimumWidth ( 250 );
        mainLayout->addWidget( imageLabelXY , 0 , 3 , 1 , 1 );

        imageLabelYZ = new QLabel();
        imageLabelYZ->setMaximumHeight( 250 );
        imageLabelYZ->setMaximumWidth ( 250 );
        mainLayout->addWidget( imageLabelYZ , 1 , 3 , 1 , 1 );

        imageLabelZX = new QLabel();
        imageLabelZX->setMaximumHeight( 250 );
        imageLabelZX->setMaximumWidth ( 250 );
        mainLayout->addWidget( imageLabelZX , 2 , 3 , 1 , 1 );

        setLayout(mainLayout);
        this->resize( 1024 , 768 );
        currentGlWidget = controlPanel;
        isShiftDown = false;
}

void myWindow::setCurrentGlWidget()
{
    QImage orthoFrameXY , orthoFrameYZ , orthoFrameZX;
    this->controlPanel->grabOrhoView( orthoFrameXY , orthoFrameYZ , orthoFrameZX );

    QIcon iconXY;
    iconXY.addPixmap( QPixmap::fromImage( orthoFrameXY ) , QIcon::Normal , QIcon::On );
    this->imageLabelXY->setPixmap( iconXY.pixmap( QSize(250,250) , QIcon::Normal , QIcon::On )  );

    QIcon iconYZ;
    iconYZ.addPixmap( QPixmap::fromImage( orthoFrameYZ ) , QIcon::Normal , QIcon::On );
    this->imageLabelYZ->setPixmap( iconYZ.pixmap( QSize(250,250) , QIcon::Normal , QIcon::On )  );

    QIcon iconZX;
    iconZX.addPixmap( QPixmap::fromImage( orthoFrameZX ) , QIcon::Normal , QIcon::On );
    this->imageLabelZX->setPixmap( iconZX.pixmap( QSize(250,250) , QIcon::Normal , QIcon::On )  );

    currentGlWidget = qobject_cast< QGLWidget* >( sender() );
    this->setFocus();
}

void myWindow::keyReleaseEvent( QKeyEvent *event )
{
        switch( event->key() )
        {
            case Qt::Key_Shift: isShiftDown = controlPanel->isShiftDown = false; break;
        }
}

void myWindow::keyPressEvent( QKeyEvent *event )
{
        switch( event->key() )
        {
            case Qt::Key_Escape: close(); break;
            case Qt::Key_Shift: isShiftDown = controlPanel->isShiftDown = true; break;
            case Qt::Key_Up:
            case Qt::Key_Down:
                {
                    int sign = 1 + -2*int(event->key()==Qt::Key_Down);
                    if( isShiftDown )
                    {
                        if( !controlPanel->doneUpdate ) return;
                        else controlPanel->doneUpdate = false;
                        controlPanel->viewPlane.position += controlPanel->viewPlane.normal * ( 1.0 / controlPanel->resZ * sign );
                        controlPanel->viewPlane.distance = controlPanel->viewPlane.normal.dot( controlPanel->viewPlane.position );
                        setCurrentGlWidget();
                        controlPanel->sliceNumber += sign;
                        //printf( "sliceNumber: %d\n" , controlPanel->sliceNumber );
                    }
                    else
                    {
                        controlPanel->camera.moveForward( 0.03 * sign );
                        if( controlPanel->OrthoProj )
                        {
                            controlPanel->orthoProjSize -= 0.1*sign;
                            controlPanel->setProjection( controlPanel->currentWidth , controlPanel->currentHeight , true );
                        }
                    }
                    break;
                }
            case Qt::Key_O:
                {
                    controlPanel->OrthoProj = !controlPanel->OrthoProj;
                    controlPanel->setProjection( controlPanel->width() , controlPanel->height() , controlPanel->OrthoProj );
                    break;
                }

            case Qt::Key_1:
                {
                    this->controlPanel->viewPlane = Plane3D( Point3D(1,0,0) , Point3D( 0.5/controlPanel->resZ , 0.5 , 0.5 ) );
                    break;
                }
            case Qt::Key_2:
                {
                    this->controlPanel->viewPlane = Plane3D( Point3D(0,1,0) , Point3D( 0.5 , 0.5/controlPanel->resZ  , 0.5 ) );
                    break;
                }
            case Qt::Key_3:
                {
                    this->controlPanel->viewPlane = Plane3D( Point3D(0,0,1) , Point3D( 0.5 , 0.5 , 0.5/controlPanel->resZ ) );
                    break;
                }

            case Qt::Key_4:
            case Qt::Key_R:
            {
                this->controlPanel->viewPlane = Plane3D( Point3D(0,0,1) , Point3D( 0.5 , 0.5 , 0.5/controlPanel->resZ + 0.5 ) );
                break;
            }
            case '!':
            {
                this->controlPanel->camera.position  = Point3D( 1.0f , 0.5f , 0.5f );
                this->controlPanel->camera.direction = Point3D(-1,0,0);
                this->controlPanel->camera.up        = Point3D(0,1,0);
                this->controlPanel->camera.right     = Point3D(0,0,-1);
                break;
            }
            case '@':
            {
                this->controlPanel->camera.position  = Point3D( 0.5f , 1.0f , 0.5f );
                this->controlPanel->camera.direction = Point3D(0,-1,0);
                this->controlPanel->camera.up        = Point3D(0,0,-1);
                this->controlPanel->camera.right     = Point3D(1,0,0);
                break;
            }
            case '#':
            {
                this->controlPanel->camera.position  = Point3D( 0.5f , 0.5f , 2.7f );
                this->controlPanel->camera.direction = Point3D(0,0,-1);
                this->controlPanel->camera.up        = Point3D(0,1,0);
                this->controlPanel->camera.right     = Point3D(1,0,0);
                this->controlPanel->orthoProjSize = 0.55;
                if(this->controlPanel->OrthoProj) this->controlPanel->setProjection( this->controlPanel->width() , this->controlPanel->height() , true );

                this->controlPanel->sliceNumber=1;
                break;
            }
            case Qt::Key_W:
                {
                    if( isShiftDown )  controlPanel->camera.rotateUp( Point3D(.5,.5,.5) , PI/8  );
                    else               controlPanel->camera.rotateUp( Point3D(.5,.5,.5) , 0.025 );
                    break;
                }
            case Qt::Key_Q:
                {
                    if( isShiftDown )  controlPanel->camera.rotateUp( Point3D(.5,.5,.5) , -PI/8  );
                    else               controlPanel->camera.rotateUp( Point3D(.5,.5,.5) , -0.025 );
                    break;
                }
            case Qt::Key_Z:
                {
                    if( isShiftDown )  controlPanel->camera.rotateRight( Point3D(.5,.5,.5) , PI/8  );
                    else               controlPanel->camera.rotateRight( Point3D(.5,.5,.5) , 0.025 );
                    break;
                }
            case Qt::Key_A:
                {
                    if( isShiftDown )  controlPanel->camera.rotateRight( Point3D(.5,.5,.5) , -PI/8  );
                    else               controlPanel->camera.rotateRight( Point3D(.5,.5,.5) , -0.025 );
                    break;
                }
            case Qt::Key_X:
                {
                    if( isShiftDown )  controlPanel->camera.rotateDir( Point3D(.5,.5,.5) , PI/8  );
                    else               controlPanel->camera.rotateDir( Point3D(.5,.5,.5) , 0.025 );
                    break;
                }
            case Qt::Key_S:
                {
                    if( isShiftDown )  controlPanel->camera.rotateDir( Point3D(.5,.5,.5) , -PI/8  );
                    else               controlPanel->camera.rotateDir( Point3D(.5,.5,.5) , -0.025 );
                    break;
                }
            case ']':
                {
                    controlPanel->camera.moveForward( 0.2 );
                    break;
                }
            case '[':
                {
                    controlPanel->camera.moveForward( -0.2 );
                    break;
                }
            case '+':
                {
                    this->controlPanel->overlay++;
                    printf("overlay: %d\n",controlPanel->overlay);
                    break;
                }
            case '-':
                {
                    this->controlPanel->overlay--;
                    printf("overlay: %d\n",controlPanel->overlay);
                    break;
                }
            case '>':
                {
                    this->controlPanel->sliceSpacing++;
                    printf("spacing: %f\n",controlPanel->sliceSpacing);
                    break;
                }
            case '<':
                {
                    this->controlPanel->sliceSpacing--;
                    printf("spacing: %f\n",controlPanel->sliceSpacing);
                    break;
                }
            case Qt::Key_T:
                {
                    controlPanel->drawTails = !controlPanel->drawTails;
                    break;
                }
            case Qt::Key_B:
                {
                    controlPanel->drawViewBBox = !controlPanel->drawViewBBox;
                    break;
                }
            case Qt::Key_F5:
                {
                    controlPanel->isUsingShader = !controlPanel->isUsingShader;
                    if( controlPanel->isUsingShader ) printf("Custom Shaders: ON \n");
                    else                              printf("Custom Shaders: OFF\n");
                }
        }
}
