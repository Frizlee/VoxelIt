#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <iostream>
#include <regex>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
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
    if (!experimental::filesystem::exists(filePath))
        throw runtime_error("Specified file path not found.");

    Assimp::Importer importer;
    auto scene = importer.ReadFile(
        filePath.string(),
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    auto mesh = scene->mMeshes[0];
    vector<Vertex> vertices;
    vector<Face> faces;
    vertices.reserve(mesh->mNumVertices);
    faces.reserve(mesh->mNumFaces * 3);
    std::transform(mesh->mVertices, mesh->mVertices + mesh->mNumVertices, back_inserter(vertices), [](aiVector3D &v) {
        return Vertex(glm::vec3(v.x, v.y, v.z));
    });
    std::transform(mesh->mFaces, mesh->mFaces + mesh->mNumFaces, back_inserter(faces), [](aiFace &v) {
        return Face(vector<uint16_t>(v.mIndices, v.mIndices + v.mNumIndices));
    });

    return dynamic_pointer_cast<Resource>(
        make_shared<Mesh>(std::move(vertices), std::move(faces))
    );
}
