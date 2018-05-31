#include "Application.hpp"
#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <VoxelIt/JsonSerializers.hpp>
#include <VoxelIt/MeshShapeConverter.hpp>
#include <memory>
#include <iostream>
using namespace std;
using namespace vit;


Application::Application()
{
    mImporter.registerImporter(make_shared<vit::ObjImporter>());
}

void Application::setArgs(vector<string>& args)
{
    mArgs = args;
}

void Application::run()
{
    if (!checkArgs())
        return;

    auto obj = mImporter.import<vit::Mesh>(mArgs.at(1));
    MeshShapeConverter converter(1);
    auto voxelObj = converter.getShapeFromMesh(obj);
    auto voxelMesh = converter.getMeshFromShape(voxelObj);
    mImporter.saveResource(voxelMesh, "exporeted.obj");
}

bool Application::checkArgs()
{
    if (mArgs.size() < 2)
    {
        cout << "Invalid arguments" << endl;
        return false;
    }

    return true;
}

