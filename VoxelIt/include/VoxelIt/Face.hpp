#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>
#include <nlohmann\json.hpp>

namespace vit
{
    /// Represents faces of a mesh.
    class Face
    {
    public:
        /// Default constructor.
        VOXELIT_API Face();

        /// Constructor for copying indices collection.
        /// \param [in] indices - collection of indices.
        VOXELIT_API Face(std::vector<uint16_t>& indices);

        /// Constructor for moving indices collection.
        /// \param [in] indices - collection of indices
        VOXELIT_API Face(std::vector<uint16_t>&& indices);

        /// Returns count of indices in face.
        /// \return number of indices.
        const size_t VOXELIT_API getIndexCount() const;

        /// Returns collection of indices in face.
        /// \return collection of indices.
        const std::vector<uint16_t> VOXELIT_API getIndices() const;

    private:
        std::vector<uint16_t> mIndices;
    };
}

