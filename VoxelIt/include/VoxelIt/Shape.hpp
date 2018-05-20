#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Resource.hpp>
#include <VoxelIt/Voxel.hpp>
#include <vector>

namespace vit
{
    class Shape : public Resource
    {
    public:
        VOXELIT_API Shape();
        VOXELIT_API Shape(float voxelSize, std::vector<Voxel>& voxels);
        VOXELIT_API Shape(float voxelSize, std::vector<Voxel>&& voxels);

        float VOXELIT_API getVoxelSize() const;
        void VOXELIT_API setVoxelSize(float scale);
        const std::vector<Voxel> VOXELIT_API getVoxels() const;

    private:
        float mVoxelSize;
        std::vector<Voxel> mVoxels;

    };
}

