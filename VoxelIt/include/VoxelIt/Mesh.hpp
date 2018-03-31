#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
#include <vector>

namespace vit
{
    class VOXELIT_API Mesh
    {
    public:
        Mesh();

    private:
        std::vector<uint16_t> mIndices;
        std::vector<Vertex> mVertices;
    };
}