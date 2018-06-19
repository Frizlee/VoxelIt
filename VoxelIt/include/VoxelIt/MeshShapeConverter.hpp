#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Shape.hpp>
#include <VoxelIt/Mesh.hpp>

namespace vit
{
    /// Performs conversion from Mesh with vertices to Shape with voxels and the other way.
    class MeshShapeConverter
    {
    public:
        /// Default consturctor.
        /// \param [in] voxelSize - size of voxel in units.
        /// \param [in] overrideSize - override Shape voxel size when saving.
        VOXELIT_API MeshShapeConverter(float voxelSize = 1.0f, bool overrideSize = false);

        /// Converts Mesh to Shape.
        /// \param [in] mesh - pointer to Mesh object.
        /// \return pointer to Shape object.
        std::shared_ptr<Shape> VOXELIT_API getShapeFromMesh(std::shared_ptr<const Mesh> mesh);

        /// Converts Shape to Mesh.
        /// \param [in] shape - pointer to Shape object.
        /// \return pointer to Mesh object.
        std::shared_ptr<Mesh> VOXELIT_API getMeshFromShape(std::shared_ptr<const Shape> shape);

        /// Returns specified voxel size.
        /// \return voxel Size.
        float VOXELIT_API getVoxelSize() const;

        /// Sets voxel size.
        /// \param [in] voxelSize - voxel size.
        void VOXELIT_API setVoxelSize(float voxelSize);

        /// Returns override size flag.
        /// \return override size flag.
        bool VOXELIT_API getOverrideSize() const;

        /// Sets override size flag.
        /// \param overrideSize - new override size flag.
        void VOXELIT_API setOverrideSize(bool overrideSize);

    private:
        glm::vec4 getTriangleBoundingBox(glm::vec2 a, glm::vec2 b, glm::vec2 c);
        bool checkIntersect(glm::vec2 rectOrig, float width, glm::vec2 a, glm::vec2 b, glm::vec2 c);
        bool checkPointInTriangle(glm::vec2 p, glm::vec2 a, glm::vec2 b, glm::vec2 c);
        bool checkPointInRectangle(glm::vec2 p, glm::vec2 rectOrig, float width);
        float planeFunc(glm::vec3 a, glm::vec3 b, glm::vec3 c, float x, float y, float voxelSize);

        float mVoxelSize;
        bool mOverrideSize;
    };
}
