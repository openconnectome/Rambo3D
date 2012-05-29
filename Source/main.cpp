#include <QApplication>
#include <iostream>
#include "myWindow.h"
#include "geometry.h"
#include "CmdLineParser.h"

#include <qfile.h>
#include <qtextstream.h>
#include <QHash>
#include <vector>

//
// For CVT
//
# include <cstdlib>
# include <cmath>
# include <ctime>
# include <iostream>
# include <iomanip>
# include <cstring>
//using namespace std;
//# include "cvt.h"


//////////////
// Comments //
//////////////
cmdLineReadable       ReadURL( "url" );
cmdLineString         Image( "img" ) , Annotation( "ano" ) , ImageUrl( "imgUrl" ) , AnnotationUrl( "anoUrl" );
cmdLineIntArray< 3 >  DataRes( "dRes" );
cmdLineReadable* params[]={ &ReadURL , &Image , &Annotation , &ImageUrl , &AnnotationUrl , &DataRes };

void ShowUsage( char* ex )
{
        printf( "\n");
        printf( "Usage: %s\n" , ex );
        printf( "\n");
        printf( "\t--%s\t<X-res> <Y-res> <Z-res>\n" , DataRes.name    );
        printf( "\t--%s/%s\t<input 3D image>       \n" , Image.name      , ImageUrl.name      );
        printf( "\t--%s/%s\t<input 3D annotation>  \n" , Annotation.name , AnnotationUrl.name );
}


int main( int argc , char *argv[] )
{
/*
    std::vector< std::vector< float > > colors;
    getRandomColors( 1000 , colors , true );
return EXIT_SUCCESS;
*/


    cmdLineParse( argc-1 , &argv[1] , sizeof(params) / sizeof(cmdLineReadable*) , params , 0 );

    if( ReadURL.set )
    {
        std::string anoString;
        printf("Annotation URL : ");
        std::cin>>anoString;
        AnnotationUrl.value = (char*)anoString.c_str();

        std::string imgString;
        printf("3D Image URL   : ");
        std::cin>>imgString;
        ImageUrl.value = (char*)imgString.c_str();

        AnnotationUrl.set = ImageUrl.set = true;
    }

    if( !DataRes.set || (!Image.set&&!ImageUrl.set) || (!Annotation.set&&!AnnotationUrl.set)  )
    {
        if( !Image.set      && !ImageUrl.set      ) printf("[ERROR] did not specify the image file...\n"     );
        if( !Annotation.set && !AnnotationUrl.set ) printf("[ERROR] did not specify the annotation file...\n");
        if( !DataRes.set                          ) printf("[ERROR] did not specify the data resolution...\n");
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

    // unbelievable bug.... system() messed up AnnotationUrl.value.....
    char imgCommand[512];
    if( ImageUrl.set )
    {
        sprintf( imgCommand , "hdf5MakePNGs_ming.py %s img.data" , ImageUrl.value      );
        Image.value      = (char*)"img.data";
    }
    char anoCommand[512];
    if( AnnotationUrl.set )
    {
        sprintf( anoCommand , "hdf5MakePNGs_ming.py %s ano.data" , AnnotationUrl.value );
        Annotation.value = (char*)"ano.data";
    }
    if( ImageUrl.set      ) system( imgCommand );
    if( AnnotationUrl.set ) system( anoCommand );

    QApplication app( argc , argv );
    myWindow window( Image.value , Annotation.value , DataRes.values[0] , DataRes.values[1] , DataRes.values[2] );
    window.show();
    return app.exec();
}
