#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <iostream>
#include <regex>
#include <assimp/Importer.hpp>
#include <assimp/Exporter.hpp>
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

bool ObjImporter::save(shared_ptr<Resource> resource, experimental::filesystem::path filePath)
{
    auto mesh = dynamic_pointer_cast<Mesh>(resource);
    Assimp::Exporter exporter;
    aiScene scene;
    scene.mRootNode = new aiNode();
    scene.mMaterials = new aiMaterial*[1];
    scene.mMaterials[0] = new aiMaterial();
    scene.mNumMaterials = 1;
    scene.mMeshes = new aiMesh*[1];
    scene.mMeshes[0] = new aiMesh();
    scene.mNumMeshes = 1;
    scene.mMeshes[0]->mMaterialIndex = 0;
    scene.mRootNode->mMeshes = new unsigned int[1];
    scene.mRootNode->mMeshes[0] = 0;
    scene.mRootNode->mNumMeshes = 1;

    auto pMesh = scene.mMeshes[0];
    auto vertices = mesh->getVertices();
    auto faces = mesh->getFaces();

    pMesh->mVertices = new aiVector3D[vertices.size()];
    pMesh->mNumVertices = vertices.size();

    for (auto it = begin(vertices); it != end(vertices); ++it)
    {
        auto pos = it->getPosition();
        pMesh->mVertices[it - begin(vertices)] = aiVector3D(pos.x, pos.y, pos.z);
    }

    pMesh->mFaces = new aiFace[faces.size()];
    pMesh->mNumFaces = faces.size();

    for (auto it = begin(faces); it != end(faces); ++it) 
    {
        aiFace& face = pMesh->mFaces[it - begin(faces)];
        auto indices = it->getIndices();

        face.mIndices = new unsigned int[indices.size()];
        face.mNumIndices = indices.size();

        for (auto it2 = begin(indices); it2 != end(indices); ++it2)
            face.mIndices[it2 - begin(indices)] = *it2;
    }

    exporter.Export(&scene, "obj", filePath.string());
    return true;
}
