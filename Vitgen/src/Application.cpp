#include "Application.hpp"
#include <VoxelIt/ObjImporter.hpp>
#include <VoxelIt/Mesh.hpp>
#include <VoxelIt/JsonSerializers.hpp>
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
    auto bBox = monkey->getBoundingBox();

    cout << setw(4) << "lower:\n" << nlohmann::json(bBox.lower)
        << "\nupper:\n" << nlohmann::json(bBox.upper) << std::endl;
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

