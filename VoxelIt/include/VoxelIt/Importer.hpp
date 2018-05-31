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
        
        template<typename T>
        std::shared_ptr<T> import(std::experimental::filesystem::path filePath);
        std::shared_ptr<Resource> VOXELIT_API importResource(std::experimental::filesystem::path filePath);
        bool VOXELIT_API saveResource(std::shared_ptr<Resource> resource, std::experimental::filesystem::path filePath);
        void VOXELIT_API registerImporter(std::shared_ptr<IResourceImporter> importer);

    private:
        std::unordered_map<std::string, std::shared_ptr<IResourceImporter>> mImporters;
    };

    template<typename T>
    inline std::shared_ptr<T> Importer::import(std::experimental::filesystem::path filePath)
    {
        static_assert(std::is_base_of<Resource, T>::value);
        return std::dynamic_pointer_cast<T>(importResource(filePath));
    }
}
