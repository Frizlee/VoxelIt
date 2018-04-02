#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Resource.hpp>
#include <string>
#include <vector>
#include <filesystem>

namespace vit
{
    class IResourceImporter
    {
    public:
        virtual VOXELIT_API ~IResourceImporter() {};
        virtual std::vector<std::experimental::filesystem::path> VOXELIT_API getSupportedExtensions() = 0;
        virtual std::shared_ptr<Resource> VOXELIT_API import(std::experimental::filesystem::path filePath) = 0;
    };
}
