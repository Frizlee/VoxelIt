#include <VoxelIt/Voxel.hpp>
using namespace vit;
using namespace std;
using glm::vec3;
using glm::tvec3;


Voxel::Voxel(tvec3<int32_t> position, vec3 color)
    : mPosition(position), mColor(color)
{
}

const tvec3<int32_t> VOXELIT_API Voxel::getPosition() const
{
    return mPosition;
}

void VOXELIT_API Voxel::setPosition(tvec3<int32_t>& position)
{
    mPosition = position;
}

const vec3 VOXELIT_API Voxel::getColor() const
{
    return mColor;
}

void VOXELIT_API Voxel::setColor(vec3& color)
{
    mColor = color;
}

