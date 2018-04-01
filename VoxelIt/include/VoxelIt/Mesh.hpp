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

    private:
        std::vector<uint16_t> mIndices;
        std::vector<Vertex> mVertices;
    };
}