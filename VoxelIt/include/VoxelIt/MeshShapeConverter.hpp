#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Shape.hpp>
#include <VoxelIt/Mesh.hpp>

namespace vit
{
    class MeshShapeConverter
    {
    public:
        VOXELIT_API MeshShapeConverter(float voxelSize = 1.0f, bool overrideSize = false);

        std::shared_ptr<Shape> VOXELIT_API getShapeFromMesh(std::shared_ptr<const Mesh> mesh);
        std::shared_ptr<Mesh> VOXELIT_API getMeshFromShape(std::shared_ptr<const Shape> shape);
        float VOXELIT_API getVoxelSize() const;
        void VOXELIT_API setVoxelSize(float voxelSize);
        bool VOXELIT_API getOverrideSize() const;
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
