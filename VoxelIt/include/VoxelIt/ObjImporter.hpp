#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/IResourceImporter.hpp>

namespace vit
{
    /// Imports resources form files with .obj extension.
    class ObjImporter : public IResourceImporter
    {
    public:
        /// Default constructor.
        VOXELIT_API ObjImporter();

        /// Returns file extensions supported by importer.
        virtual std::vector<std::experimental::filesystem::path> VOXELIT_API getSupportedExtensions() override;

        /// Imports resource from specified file.
        /// \param [in] filePath - path to resource file.
        /// \return pointer to Resource.
        virtual std::shared_ptr<Resource> VOXELIT_API import(std::experimental::filesystem::path filePath) override;

        /// Saves resource in specified location.
        /// \param [in] filePath - output file path.
        /// \return true, if completed successfuly otherwise an error occured.
        virtual bool VOXELIT_API save(std::shared_ptr<Resource> resource, std::experimental::filesystem::path filePath) override;
    };
}
