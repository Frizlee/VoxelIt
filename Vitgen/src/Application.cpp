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

    auto monkey = mImporter.import<vit::Mesh>(mArgs.at(1));
    MeshShapeConverter converter(0.02);
    auto voxelMonkey = converter.getShapeFromMesh(monkey);
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

