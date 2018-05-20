#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
#include <VoxelIt/Face.hpp>
#include <VoxelIt/Resource.hpp>
#include <vector>

namespace vit
{
    class Mesh : public Resource
    {
    public:
        struct BoundingBox 
        {
            VOXELIT_API BoundingBox(glm::vec3 lower = glm::vec3(), glm::vec3 upper = glm::vec3());

            glm::vec3 lower;
            glm::vec3 upper;
        };

        VOXELIT_API Mesh();
        VOXELIT_API Mesh(std::vector<Vertex>& vertices, std::vector<Face>& faces);
        VOXELIT_API Mesh(std::vector<Vertex>&& vertices, std::vector<Face>&& faces);

        const std::vector<Vertex> VOXELIT_API getVertices() const;
        const std::vector<Face> VOXELIT_API getFaces() const;
        BoundingBox VOXELIT_API getBoundingBox() const;

    private:
        void onChange();

        std::vector<Face> mFaces;
        std::vector<Vertex> mVertices;
        mutable bool mIsBoundingBox;
        mutable BoundingBox mBoundingBox;
    };
}