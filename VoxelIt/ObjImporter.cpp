#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <iostream>
#include <regex>
using namespace vit;
using namespace std;

ObjImporter::ObjImporter()
{
}

vector<experimental::filesystem::path> ObjImporter::getSupportedExtensions()
{
    return vector<experimental::filesystem::path>{ ".obj" };
}

shared_ptr<Resource> ObjImporter::import(experimental::filesystem::path filePath)
{
    auto vertex = regex("^v () () ()");
    auto normal = regex("^vn () ()");
    auto face = regex("^f ()/()/() ()/()/() ()/()/()");

    auto vertices = vector<Vertex>
    {
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } },
        { { 0.0f, 0.0f, 0.0f } }
    };

    auto indices = vector<uint16_t>{ 1, 2, 3, 5 };

    auto mesh = make_shared<Mesh>(std::move(vertices), std::move(indices));
    return dynamic_pointer_cast<Resource>(mesh);
}
