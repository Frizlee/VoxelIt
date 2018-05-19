#include <VoxelIt\Face.hpp>
using namespace vit;
using namespace std;

Face::Face()
{
}

Face::Face(vector<uint16_t>& indices)
    : mIndices(indices)
{
}

Face::Face(vector<uint16_t>&& indices)
{
    swap(mIndices, indices);
}

const VOXELIT_API size_t Face::getIndexCount() const
{
    return mIndices.size();
}

const VOXELIT_API std::vector<uint16_t> Face::getIndices() const
{
    return mIndices;
}
