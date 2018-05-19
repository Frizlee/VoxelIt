#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>
#include <nlohmann\json.hpp>

namespace vit
{
    class Vertex
    {
    public:
        VOXELIT_API Vertex(glm::vec3 position = glm::vec3(), glm::vec3 color = glm::vec3(), glm::vec3 normal = glm::vec3());

        const glm::vec3 VOXELIT_API getPosition() const;
        void VOXELIT_API setPosition(glm::vec3& position);
        const glm::vec3 VOXELIT_API getColor() const;
        void VOXELIT_API setColor(glm::vec3& color);
        const glm::vec3 VOXELIT_API getNormal() const;
        void VOXELIT_API setNormal(glm::vec3& normal);

    private:
        glm::vec3 mPosition;
        glm::vec3 mColor;
        glm::vec3 mNormal;
    };
}

