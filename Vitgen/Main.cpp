#include <iostream>
#include <VoxelIt/Importer.hpp>
#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <VoxelIt/JsonSerializers.hpp>
using nlohmann::json;
using namespace std;

int main(int argc, char **argv)
{
    try
    {
        vit::Importer imp;
        imp.registerImporter(make_shared<vit::ObjImporter>());

        auto monkey = dynamic_pointer_cast<vit::Mesh>(imp.import("monkey.obj"));
    }
    catch (runtime_error err)
    {
        cerr << err.what() << endl;
    }
    return 0;
}