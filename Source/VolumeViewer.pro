DEFINES += GLEWPATH_UNIX=/home/jhong/Documents/glew-1.7.0/lib

TEMPLATE = app
QT += opengl
CONFIG += console


# This line manually links this code to your libGLEW library.
# Please point it to where libGLEW is located in your machine.
#LIBS += C:/QtSDK/glew-1.5.2/lib/libglew32.dll.a
LIBS += /home/jhong/Documents/glew-1.7.0/lib/libGLEW.a -lGLU


# The cache library that I was using requires Boost. In order to get Boost running, I manually linked to it here.
# (Rumor has it that if Boost is properly installed on your machine, you do not need this line to run.)
LIBS += /usr/lib/libboost_thread-mt.so


# Code I tried to use previously required this compiler flag to compile.
# I no longer use this code, but I kept it here because figuring out how to add compiler flags to Qt was painful.
# This is how you add compiler flags to Qt.
#QMAKE_CXXFLAGS += -std=c++0x


INCLUDEPATH += .
HEADERS += ./myWindow.h	\
    ControlPanel.h 	\
    glCamera.h 		\
    geometry.h 		\
    CmdLineParser.h \
    DynamicVoxelHierarchy/VoxelOracle.h \
    DynamicVoxelHierarchy/voxel.h \
    DynamicVoxelHierarchy/CacheMaintain.h \
    DynamicVoxelHierarchy/HierarchyRenderer.h\
    \
    DynamicVoxelHierarchy/lru_cache/src/lru_cache.h

SOURCES += ./main.cpp 	\
    myWindow.cpp 	\
    ControlPanel.cpp 	\
    glCamera.cpp 	\
    geometry.cpp 	\
    CmdLineParser.cpp \
    DynamicVoxelHierarchy/VoxelOracle.cpp \
    DynamicVoxelHierarchy/voxel.cpp \
    DynamicVoxelHierarchy/CacheMaintain.cpp \
    DynamicVoxelHierarchy/HierarchyRenderer.cpp\
    \
    DynamicVoxelHierarchy/lru_cache/src/lru_cache.cpp

