#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
#include <VoxelIt/Resource.hpp>
#include <vector>

namespace vit
{
    class Mesh : public Resource
    {
    public:
        VOXELIT_API Mesh();

        const std::vector<Vertex> VOXELIT_API getVertices() const;
        void VOXELIT_API setVertices(std::vector<Vertex>& vertices);
        const std::vector<uint16_t> VOXELIT_API getIndices() const;
        void VOXELIT_API setIndices(std::vector<uint16_t>& indices);

    private:
        std::vector<uint16_t> mIndices;
        std::vector<Vertex> mVertices;
    };
}