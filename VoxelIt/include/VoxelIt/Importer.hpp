#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Resource.hpp>
#include <VoxelIt/IResourceImporter.hpp>
#include <memory>
#include <filesystem>
#include <unordered_map>

namespace vit
{
    class Importer
    {
    public:
        VOXELIT_API Importer();
        std::shared_ptr<Resource> VOXELIT_API import(std::experimental::filesystem::path filePath);
        void VOXELIT_API registerImporter(std::shared_ptr<IResourceImporter> importer);

    private:
        std::unordered_map<std::string, std::shared_ptr<IResourceImporter>> mImporters;
    };
}
