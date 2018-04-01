#include <VoxelIt/Mesh.hpp>
#include <iostream>
using namespace vit;
using namespace std;

Mesh::Mesh()
{
}

const vector<Vertex> Mesh::getVertices() const
{
    return mVertices;
}

void Mesh::setVertices(vector<Vertex>& vertices)
{
    mVertices = vertices;
}

const vector<uint16_t> Mesh::getIndices() const
{
    return mIndices;
}

void Mesh::setIndices(vector<uint16_t>& indices)
{
    mIndices = indices;
}
