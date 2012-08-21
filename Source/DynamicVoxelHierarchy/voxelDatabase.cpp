#include "voxelDatabase.h"

using namespace std;

voxelDatabase::voxelDatabase()
{
    //inefficientDatabase = std::vector<FILE*>(0);

}

void voxelDatabase::temp()
{

}




void voxelDatabase::addFile(string ID)
{
    //FILE* f;
    std::ofstream myfile;

    //write ID into file f
    myfile.open(ID.data());
    myfile << ID;
    myfile.close();

    //inefficientDatabase.push_back(f);
    //return f;
}


void voxelDatabase::addFile(Voxel v)
{
    string ID = v.getID();

    string fileName;
    fileName.append(ID.data());
    fileName.append(".voxel");

    std::ofstream ofs(fileName.data(), ios::binary);
    ofs.write((char *)&v, sizeof(v));
}



Voxel voxelDatabase::getFile(string ID)
{
    Voxel v;

    string fileName;
    fileName.append(ID.data());
    fileName.append(".voxel");

    std::ifstream ifs(fileName.data(), ios::binary);

    if(ifs.is_open())
    {
        ifs.read((char *)&v, sizeof(v));
        v.getID();
        return v;
    }
    else
    {

        v = Voxel(ID);
        addFile(v);
        return v;
    }


}
