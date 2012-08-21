
#include <GL/glew.h>

#include <QApplication>
#include "myWindow.h"
#include "CmdLineParser.h"

cmdLineString         Image( "img" ) , Annotation( "ano" );
cmdLineIntArray< 3 >  DataRes( "dRes" );
cmdLineReadable* params[]={ &Image , &Annotation , &DataRes };



#include "DynamicVoxelHierarchy/HierarchyRenderer.h"
#include "DynamicVoxelHierarchy/CacheMaintain.h"

#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::cout;
using std::endl;


void test1();
void test2();
void test3();




void ShowUsage( char* ex )
{
        printf( "\n");
        printf( "Usage: %s\n" , ex );
        printf( "\n");
        printf( "\t--%s\t<X-res> <Y-res> <Z-res>\n" , DataRes.name    );
        printf( "\t--%s\t<input 3D image>       \n" , Image.name      );
        printf( "\t--%s\t<input 3D annotation>  \n" , Annotation.name );
}


int main( int argc , char *argv[] )
{

    cmdLineParse( argc-1 , &argv[1] , sizeof(params) /
sizeof(cmdLineReadable*) , params , 0 );

    if( !DataRes.set || !Image.set || !Annotation.set )
    {
        if( !Image.set      ) printf("[ERROR] did not specify the image file...\n");
        if( !Annotation.set ) printf("[ERROR] did not specify the annotation file...\n");
        if( !DataRes.set    ) printf("[ERROR] did not specify the data resolution...\n");
        ShowUsage( argv[0] );
        return EXIT_FAILURE;
    }

    int paramNum=sizeof(params)/sizeof(cmdLineReadable*);
    char valueString[1024];
    for( int i=0 ; i<paramNum ; i++ )
        if(params[i]->set)
        {
                params[i]->writeValue( valueString );
                printf( "\t--%s %s \n" , params[i]->name , valueString );
        }

    glewInit();

    QApplication app( argc , argv );
    myWindow window( Image.value , Annotation.value ,
DataRes.values[0] , DataRes.values[1] , DataRes.values[2] );
    window.show();
    return app.exec();



    //--------------------------------------------------------

    //test2();

    //test3();
}


void test1()
{
    CacheMaintain *cachemaintain = new CacheMaintain();

    string a = "one";
    string b = "two";

    cachemaintain->insertVoxelData(a,Voxel(a),2);

    Voxel v = cachemaintain->getVoxelData(a);
    Voxel v2 = cachemaintain->getVoxelData(a);

    cachemaintain->printCache();
}

void test2()
{
    // Voxel Oracle
    int zoomedIn = 0;
    Plane3D viewingPlane = Plane3D();
    VoxelOracle* voxeloracle = new VoxelOracle(zoomedIn,viewingPlane);

    //Cache maintain
    int cacheCapacity = 10;
    int hierarchySize = 10;
    CacheMaintain* cachemaintain = new
CacheMaintain(cacheCapacity,hierarchySize);

    //Hierarchy Renderer
    HierarchyRenderer* hierarchyRenderer = new
HierarchyRenderer(voxeloracle,cachemaintain);



    voxeloracle->setZoomedIn(0);
    std::vector<Voxel>* voxelsNeeded = new std::vector<Voxel>();
    voxelsNeeded->clear();
    voxelsNeeded->push_back(Voxel("A",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("B",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("C",voxeloracle->getZoomedIn()));
    voxeloracle->setManualControl(*voxelsNeeded);

    hierarchyRenderer->renderDynamicVoxels();



    voxeloracle->setZoomedIn(0);
    voxelsNeeded->clear();
    voxelsNeeded->push_back(Voxel("A",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("B",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("C",voxeloracle->getZoomedIn()));
    voxeloracle->setManualControl(*voxelsNeeded);

    hierarchyRenderer->renderDynamicVoxels();

}


void test3()
{
    // Voxel Oracle
    int zoomedIn = 0;
    Plane3D viewingPlane = Plane3D();
    VoxelOracle* voxeloracle = new VoxelOracle(zoomedIn,viewingPlane);

    //Cache maintain
    int cacheCapacity = 10;
    int hierarchySize = 10;
    CacheMaintain* cachemaintain = new
CacheMaintain(cacheCapacity,hierarchySize);

    //Hierarchy Renderer
    HierarchyRenderer* hierarchyRenderer = new
HierarchyRenderer(voxeloracle,cachemaintain);



    voxeloracle->setZoomedIn(2);
    std::vector<Voxel>* voxelsNeeded = new std::vector<Voxel>();
    voxelsNeeded->clear();
    voxelsNeeded->push_back(Voxel("A",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("B",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("C",voxeloracle->getZoomedIn()));
    voxeloracle->setManualControl(*voxelsNeeded);

    hierarchyRenderer->renderDynamicVoxels();



    voxeloracle->setZoomedIn(0);
    voxelsNeeded->clear();
    voxelsNeeded->push_back(Voxel("A",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("B",voxeloracle->getZoomedIn()));
    voxelsNeeded->push_back(Voxel("C",voxeloracle->getZoomedIn()));
    voxeloracle->setManualControl(*voxelsNeeded);

    hierarchyRenderer->renderDynamicVoxels();

}
