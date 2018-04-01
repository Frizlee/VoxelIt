#include <iostream>
#include <VoxelIt/Importer.hpp>
#include <VoxelIt/ObjImporter.hpp>
using namespace std;

int main(int argc, char **argv)
{
    try
    {
        vit::Importer imp;
        imp.registerImporter(make_shared<vit::ObjImporter>());

        auto monkey = imp.import("monkey.obj");
    }
    catch (runtime_error err)
    {
        cerr << err.what() << endl;
    }
    return 0;
}