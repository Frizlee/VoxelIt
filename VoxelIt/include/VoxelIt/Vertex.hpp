#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>

namespace vit
{
    class VOXELIT_API Vertex
    {
    public:
        Vertex(glm::vec3 position = glm::vec3(), glm::vec3 color = glm::vec3(), glm::vec3 normal = glm::vec3());

        glm::vec3 getPosition() const;
        void setPosition(glm::vec3& position);
        glm::vec3 getColor() const;
        void setColor(glm::vec3& color);
        glm::vec3 getNormal() const;
        void setNormal(glm::vec3& normal);

    private:
        glm::vec3 mPosition;
        glm::vec3 mColor;
        glm::vec3 mNormal;
    };
}

