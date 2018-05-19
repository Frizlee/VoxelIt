#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>
#include <nlohmann\json.hpp>

namespace vit
{
    class Face
    {
    public:
        VOXELIT_API Face();
        VOXELIT_API Face(std::vector<uint16_t>& indices);
        VOXELIT_API Face(std::vector<uint16_t>&& indices);

        const size_t VOXELIT_API getIndexCount() const;
        const std::vector<uint16_t> VOXELIT_API getIndices() const;

    private:
        std::vector<uint16_t> mIndices;
    };
}

