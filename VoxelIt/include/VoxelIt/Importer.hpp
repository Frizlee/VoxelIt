#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Resource.hpp>
#include <VoxelIt/IResourceImporter.hpp>
#include <memory>
#include <filesystem>
#include <unordered_map>

namespace vit
{
    /// Importer object allows to import resources from files.
    class Importer
    {
    public:
        /// Default constructor.
        VOXELIT_API Importer();
        
        /// Imports resource, returning pointer to specified type of resource.
        /// \param [in] filePath - path to resource file.
        /// \return pointer to resource of type T.
        template<typename T>
        std::shared_ptr<T> import(std::experimental::filesystem::path filePath);

        /// Imports resource, returning pointer to Resource object.
        /// \param [in] filePath - path to resource file.
        /// \return pointer to Resource.
        std::shared_ptr<Resource> VOXELIT_API importResource(std::experimental::filesystem::path filePath);

        /// Saves resource in specified location.
        /// \param [in] filePath - output file path.
        /// \return true, if completed successfuly otherwise an error occured.
        bool VOXELIT_API saveResource(std::shared_ptr<Resource> resource, std::experimental::filesystem::path filePath);

        /// Registers importer of specified type
        /// \param [in] importer - pointer to resource importer.
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
