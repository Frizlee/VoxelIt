#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/IResourceImporter.hpp>

namespace vit
{
    class ObjImporter : public IResourceImporter
    {
    public:
        VOXELIT_API ObjImporter();
        virtual std::vector<std::string> VOXELIT_API getSupportedExtensions() override;
        virtual std::shared_ptr<Resource> VOXELIT_API import(std::experimental::filesystem::path filePath) override;
    };
}
