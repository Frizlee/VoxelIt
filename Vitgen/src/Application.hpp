#pragma once
#include <VoxelIt/Importer.hpp>
#include <vector>
#include <string>

/// Main application class
class Application
{
public:
    /// Default constructor.
    Application();

    /// Pasess program arguments to the application object.
    /// \param [in] args - program arguments.
    void setArgs(std::vector<std::string>& args);

    /// Runs the program.
    void run();

private:
    bool checkArgs();

    std::vector<std::string> mArgs;
    vit::Importer mImporter;
};

