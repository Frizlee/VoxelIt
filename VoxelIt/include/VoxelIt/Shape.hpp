#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Resource.hpp>
#include <VoxelIt/Voxel.hpp>
#include <vector>

namespace vit
{
    /// Represend 3d object created form voxels.
    class Shape : public Resource
    {
    public:
        /// Default constructor.
        VOXELIT_API Shape();

        /// Constructor which creates object by copying voxel collection.
        /// \param [in] voxelSize - size of voxel.
        /// \param [in] voxels - collection of voxels.
        VOXELIT_API Shape(float voxelSize, std::vector<Voxel>& voxels);

        /// Constructor which creates object by moving voxel collection.
        /// \param [in] voxelSize - size of voxel.
        /// \param [in] voxels - collection of voxels.
        VOXELIT_API Shape(float voxelSize, std::vector<Voxel>&& voxels);

        /// Returns voxel size.
        /// \return size of voxel.
        float VOXELIT_API getVoxelSize() const;

        /// Sets voxel size.
        /// \param [in] scale - voxel size.
        void VOXELIT_API setVoxelSize(float scale);

        /// Gets voxel collection.
        /// \return voxel collection.
        const std::vector<Voxel> VOXELIT_API getVoxels() const;

    private:
        float mVoxelSize;
        std::vector<Voxel> mVoxels;

    };
}

