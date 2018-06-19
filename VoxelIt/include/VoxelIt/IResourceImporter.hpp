#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Resource.hpp>
#include <string>
#include <vector>
#include <filesystem>

namespace vit
{
    /// Interface for resource importers.
    class IResourceImporter
    {
    public:
        /// Virtual destructor
        virtual VOXELIT_API ~IResourceImporter() {};

        /// Returns file extensions supported by importer.
        virtual std::vector<std::experimental::filesystem::path> VOXELIT_API getSupportedExtensions() = 0;

        /// Imports resource from specified file.
        /// \param [in] filePath - path to resource file.
        /// \return pointer to Resource.
        virtual std::shared_ptr<Resource> VOXELIT_API import(std::experimental::filesystem::path filePath) = 0;

        /// Saves resource in specified location.
        /// \param [in] filePath - output file path.
        /// \return true, if completed successfuly otherwise an error occured.
        virtual bool VOXELIT_API save(std::shared_ptr<Resource> resource, std::experimental::filesystem::path filePath) = 0;
    };
}
