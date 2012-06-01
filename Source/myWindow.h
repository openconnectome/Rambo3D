#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWidget>
#include <QLabel>
#include "ControlPanel.h"

class GLWidget;

class myWindow : public QWidget
{
    Q_OBJECT

public:
    myWindow( char* ImagePath , char* AnnoPath , int DataResX , int DataResY , int DataResZ );
    //~myWindow();
    void setCurrentGlWidget();

protected:
    void keyReleaseEvent( QKeyEvent *event );
    void keyPressEvent( QKeyEvent *event );

private:

    ControlPanel* controlPanel;

    QGLWidget *currentGlWidget;

    QLabel* imageLabelXY;
    QLabel* imageLabelYZ;
    QLabel* imageLabelZX;

    bool isShiftDown;
};

#endif //MYWINDOW_H
