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
        bool VOXELIT_API operator==(const Voxel &other) const;
        

    private:
        glm::tvec3<int32_t> mPosition;
        glm::vec3 mColor;
    };
}

namespace std {

    template <>
    struct hash<vit::Voxel>
    {
        std::size_t operator()(const vit::Voxel& k) const
        {
            using std::size_t;
            using std::hash;
            using std::string;

            glm::vec3 pos = k.getPosition();
            glm::vec3 col = k.getColor();

            return ((hash<float>()(pos.x)
                ^ (hash<float>()(pos.y) << 1)
                ^ (hash<float>()(pos.z) << 2)) >> 1
                ^ (hash<float>()(col.r)
                ^ (hash<float>()(col.g) << 1)
                ^ (hash<float>()(col.b) << 2)) >> 1);
        }
    };

}
