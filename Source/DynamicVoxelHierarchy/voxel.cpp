#include "voxel.h"

#include <iostream>
#include <fstream>
#include <string>

//using namespace std;
using std::string;
using std::ifstream;
using std::cout;
using std::endl;

//#include <QtOpenGL>


//** Default Constructor
Voxel::Voxel()
{
    string defaultName = "Default Name";
    char* defaultDataLocation = "test.txt";

    ID = defaultName;
    Resolution = 0;
//    ResolutionX = 512;
//    ResolutionY = 512;
//    ResolutionZ = 16;
//    dataLocation = defaultDataLocation;
}

Voxel::Voxel(string ID, int resolution)
{
    char* defaultDataLocation = "test.txt";

    this->ID = ID;
    Resolution = resolution;
//    ResolutionX = 512;
//    ResolutionY = 512;
//    ResolutionZ = 16;
//    dataLocation = defaultDataLocation;
}

//** Constructor
/*
Voxel:: Voxel(string ID , int ResolutionX , int ResolutionY , int ResolutionZ , char* dataLocation )
{
    this->ID = ID;
    this->ResolutionX = ResolutionX;
    this->ResolutionY = ResolutionY;
    this->ResolutionZ = ResolutionZ;
    this->dataLocation = dataLocation;
}
*/

/*
Voxel::Voxel(string ID, int Resolution, char *dataLocation)
{
    this->ID = ID;
    this->Resolution = Resolution;
    this->dataLocation = dataLocation;
}
*/

/*
void Voxel::printData()
{
    //Data = fopen("dataLocation","r");

    string line;
    ifstream myfile (dataLocation);
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            cout << line << endl;
        }
        myfile.close();
    }
    else cout << "Unable to open file\n";
}
*/

string Voxel::getID()
{
    return ID;
}

int Voxel::getResolution()
{
    return Resolution;
}
