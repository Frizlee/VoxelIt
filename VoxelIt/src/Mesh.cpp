#include <VoxelIt/Mesh.hpp>
#include <iostream>
using namespace vit;
using namespace std;

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<uint16_t>& indices)
    : mVertices(vertices), mIndices(indices)
{

}

Mesh::Mesh(std::vector<Vertex>&& vertices, std::vector<uint16_t>&& indices)
{   
    std::swap(mVertices, vertices);
    std::swap(mIndices, indices);
}

const vector<Vertex> Mesh::getVertices() const
{
    return mVertices;
}

/*void Mesh::setVertices(vector<Vertex>& vertices)
{
    mVertices = vertices;
}*/

const vector<uint16_t> Mesh::getIndices() const
{
    return mIndices;
}

/*void Mesh::setIndices(vector<uint16_t>& indices)
{
    mIndices = indices;
}*/
