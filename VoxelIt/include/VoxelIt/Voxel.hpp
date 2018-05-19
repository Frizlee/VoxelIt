#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>
#include <nlohmann\json.hpp>

namespace vit
{
    class Voxel
    {
    public:

        VOXELIT_API Voxel(glm::tvec3<int32_t> position = glm::tvec3<int32_t>(), glm::vec3 color = glm::vec3());

        const glm::tvec3<int32_t> VOXELIT_API getPosition() const;
        void VOXELIT_API setPosition(glm::tvec3<int32_t>& position);
        const glm::vec3 VOXELIT_API getColor() const;
        void VOXELIT_API setColor(glm::vec3& color);

    private:
        glm::tvec3<int32_t> mPosition;
        glm::vec3 mColor;
    };
}
