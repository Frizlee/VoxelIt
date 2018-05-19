#include <VoxelIt\Vertex.hpp>
using namespace vit;
using glm::vec3;


Vertex::Vertex(vec3 position, vec3 color, vec3 normal)
    : mPosition(position), mColor(color), mNormal(normal)
{
}

const vec3 Vertex::getPosition() const
{
    return mPosition;
}

void Vertex::setPosition(vec3& position)
{
    mPosition = position;
}

const vec3 Vertex::getColor() const
{
    return mColor;
}

void Vertex::setColor(vec3& color)
{
    mColor = color;
}

const vec3 Vertex::getNormal() const
{
    return mNormal;
}

void Vertex::setNormal(vec3& normal)
{
    mNormal = normal;
}

