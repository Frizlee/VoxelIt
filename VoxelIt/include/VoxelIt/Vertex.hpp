#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>
#include <nlohmann\json.hpp>

namespace vit
{
    /// 3d vertex object which consists of position, normal and color.
    class Vertex
    {
    public:
        /// Default constructor.
        /// \param [in] position - position of the vertex.
        /// \param [in] color - color of the vertex.
        /// \param [in] normal - normal of the vertex.
        VOXELIT_API Vertex(glm::vec3 position = glm::vec3(), glm::vec3 color = glm::vec3(), glm::vec3 normal = glm::vec3());

        /// Gets position of the vertex.
        /// \return position of the vertex.
        const glm::vec3 VOXELIT_API getPosition() const;

        /// Sets position of the vertex.
        /// \param [in] position - position of the vertex.
        void VOXELIT_API setPosition(glm::vec3& position);

        /// Gets color of the vertex.
        /// \return color of the vertex.
        const glm::vec3 VOXELIT_API getColor() const;

        /// Sets color of the vertex.
        /// \param [in] color - color of the vertex.
        void VOXELIT_API setColor(glm::vec3& color);

        /// Gets nromal of the vertex.
        /// \return normal of the vertex.
        const glm::vec3 VOXELIT_API getNormal() const;

        /// Sets normal of the vertex.
        /// \param [in] normal - normal of the vertex.
        void VOXELIT_API setNormal(glm::vec3& normal);

    private:
        glm::vec3 mPosition;
        glm::vec3 mColor;
        glm::vec3 mNormal;
    };
}

