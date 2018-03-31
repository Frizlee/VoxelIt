#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
#include <vector>

namespace vit
{
    class Mesh
    {
    public:
        VOXELIT_API Mesh();

    private:
        std::vector<uint16_t> mIndices;
        std::vector<Vertex> mVertices;
    };
}