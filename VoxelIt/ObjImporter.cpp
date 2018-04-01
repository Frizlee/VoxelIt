#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <iostream>
using namespace vit;
using namespace std;

ObjImporter::ObjImporter()
{
}

vector<string> ObjImporter::getSupportedExtensions()
{
    return vector<string>{ ".obj" };
}

shared_ptr<Resource> ObjImporter::import(experimental::filesystem::path filePath)
{
    auto mesh = make_shared<Mesh>();



    return dynamic_pointer_cast<Resource>(mesh);
}
