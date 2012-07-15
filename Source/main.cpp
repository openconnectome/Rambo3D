#include <GL/glew.h>

#include <QApplication>
#include "myWindow.h"
#include "CmdLineParser.h"

cmdLineString         Image( "img" ) , Annotation( "ano" );
cmdLineIntArray< 3 >  DataRes( "dRes" );
cmdLineReadable* params[]={ &Image , &Annotation , &DataRes };


#include "voxel.h"



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
    cmdLineParse( argc-1 , &argv[1] , sizeof(params) / sizeof(cmdLineReadable*) , params , 0 );

    if( !DataRes.set || !Image.set || !Annotation.set )
    {
        if( !Image.set      ) printf("[ERROR] did not specify the image file...\n"     );
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
    myWindow window( Image.value , Annotation.value , DataRes.values[0] , DataRes.values[1] , DataRes.values[2] );
    //window.show();
    //return app.exec();


    char* ImagePath = Image.value;
    char* AnnotationPath = Annotation.value;
    int resX = DataRes.values[0];
    int resY = DataRes.values[1];
    int resZ = DataRes.values[2];

    Voxel voxel(ImagePath, AnnotationPath, resX, resY, resZ);

    return 0;

}
