#include <VoxelIt/Mesh.hpp>
#include <iostream>
#include <algorithm>
using namespace vit;
using namespace std;

Mesh::Mesh()
    : mIsBoundingBox(false)
{
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Face>& faces)
    : mVertices(vertices), mFaces(faces), mIsBoundingBox(false)
{

}

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<Face>&& faces)
    : mIsBoundingBox(false)
{   
    swap(mVertices, vertices);
    swap(mFaces, faces);
}

const vector<Vertex> Mesh::getVertices() const
{
    return mVertices;
}

const vector<Face> Mesh::getFaces() const
{
    return mFaces;
}

const Mesh::BoundingBox VOXELIT_API vit::Mesh::getBoundingBox() const
{
    if (mIsBoundingBox)
        return mBoundingBox;

    if (mVertices.empty())
    {
        mIsBoundingBox = true;
        return BoundingBox();
    }

    mBoundingBox.lower = mVertices[0].getPosition();
    mBoundingBox.upper = mVertices[0].getPosition();

    for (auto& v : mVertices) 
    {
        auto& pos = v.getPosition();

        if (pos.x < mBoundingBox.lower.x)
            mBoundingBox.lower.x = pos.x;

        if (pos.y < mBoundingBox.lower.y)
            mBoundingBox.lower.y = pos.y;

        if (pos.z < mBoundingBox.lower.z)
            mBoundingBox.lower.z = pos.z;

        if (pos.x > mBoundingBox.upper.x)
            mBoundingBox.upper.x = pos.x;

        if (pos.y > mBoundingBox.upper.y)
            mBoundingBox.upper.y = pos.y;

        if (pos.z > mBoundingBox.upper.z)
            mBoundingBox.upper.z = pos.z;
    }

    mIsBoundingBox = true;
    return mBoundingBox;
}

void Mesh::onChange()
{
    mIsBoundingBox = false;
}

Mesh::BoundingBox::BoundingBox(glm::vec3 lower, glm::vec3 upper)
    : lower(lower), upper(upper)
{
}
