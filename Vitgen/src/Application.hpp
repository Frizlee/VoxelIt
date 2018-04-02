#pragma once
#include <VoxelIt/Importer.hpp>
#include <vector>
#include <string>


class Application
{
public:
    Application();

    void setArgs(std::vector<std::string>& args);
    void run();

private:
    bool checkArgs();

    std::vector<std::string> mArgs;
    vit::Importer mImporter;
};

