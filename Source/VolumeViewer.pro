TEMPLATE = app
QT += opengl
CONFIG += console
LIBS += C:/QtSDK/glew-1.5.2/lib/libglew32.dll.a
INCLUDEPATH += .
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
