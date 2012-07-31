DEFINES += GLEWPATH_UNIX=/home/jhong/Documents/glew-1.7.0/lib

TEMPLATE = app
QT += opengl
CONFIG += console
#LIBS += C:/QtSDK/glew-1.5.2/lib/libglew32.dll.a
LIBS += /home/jhong/Documents/glew-1.7.0/lib/libGLEW.a -lGLU
LIBS += /usr/lib/libboost_thread-mt.so


QMAKE_CXXFLAGS += -std=c++0x



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

