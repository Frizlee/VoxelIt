#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
#include <VoxelIt/Face.hpp>
#include <VoxelIt/Resource.hpp>
#include <vector>

namespace vit
{
    /// Represents 3d object mesh.
    class Mesh : public Resource
    {
    public:
        /// Represents a bounding box of 3d mesh.
        struct BoundingBox 
        {
            /// Default constructor.
            /// \param [in] lower - lower corner of the box.
            /// \param [in] upper - upper corner of the box which lies along the diagonal from the lower corner.
            VOXELIT_API BoundingBox(glm::vec3 lower = glm::vec3(), glm::vec3 upper = glm::vec3());

            glm::vec3 lower; ///< lower corner of the box.
            glm::vec3 upper; ///< upper corner of the box.
        };

        /// Default constructor.
        VOXELIT_API Mesh();

        /// Constructor for copying vertices and faces collection.
        /// \param [in] vertices - vertices collection.
        /// \param [in] faces - faces collection.
        VOXELIT_API Mesh(std::vector<Vertex>& vertices, std::vector<Face>& faces);

        /// Constructor for moving vertices and faces collection.
        /// \param [in] vertices - vertices collection.
        /// \param [in] faces - faces collection.
        VOXELIT_API Mesh(std::vector<Vertex>&& vertices, std::vector<Face>&& faces);

        /// Returns vertices collection.
        /// \return vertices collection.
        const std::vector<Vertex> VOXELIT_API getVertices() const;

        /// Returns faces collection.
        /// \return faces collection.
        const std::vector<Face> VOXELIT_API getFaces() const;

        /// Calculates and returns the bounding box of the mesh.
        /// \return bounding box of the mesh.
        BoundingBox VOXELIT_API getBoundingBox() const;

    private:
        void onChange();

        std::vector<Face> mFaces;
        std::vector<Vertex> mVertices;
        mutable bool mIsBoundingBox;
        mutable BoundingBox mBoundingBox;
    };
}