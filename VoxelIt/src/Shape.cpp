#include <VoxelIt\Shape.hpp>
using namespace vit;
using namespace std;


Shape::Shape()
{
}

Shape::Shape(float voxelSize, vector<Voxel>& voxels)
    : mVoxelSize(voxelSize), mVoxels(voxels)
{
}

Shape::Shape(float voxelSize, vector<Voxel>&& voxels)
    : mVoxelSize(voxelSize)
{
    swap(mVoxels, voxels);
}

float Shape::getVoxelSize() const
{
    return mVoxelSize;
}

void Shape::setVoxelSize(float voxelSize)
{
    mVoxelSize = voxelSize;
}

const vector<Voxel> Shape::getVoxels() const
{
    return mVoxels;
}

