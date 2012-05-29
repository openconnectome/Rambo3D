TEMPLATE = app
QT += opengl
CONFIG += console
LIBS += -lglew32
INCLUDEPATH += .
INCLUDEPATH += "C:\msys\1.0\home\Ming\tiff-3.9.2\libtiff"

# Input
HEADERS += ./myWindow.h	\
    ControlPanel.h 	\
    glCamera.h 		\
    geometry.h 		\
    CmdLineParser.h
SOURCES += ./main.cpp 	\
    myWindow.cpp 	\
    ControlPanel.cpp 	\
    glCamera.cpp 	\
    geometry.cpp 	\
    CmdLineParser.cpp
