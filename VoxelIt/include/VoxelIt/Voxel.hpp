#pragma once
#include <VoxelIt\Prerequisites.hpp>
#include <glm\glm.hpp>
#include <nlohmann\json.hpp>

namespace vit
{
    /// Represents main building element of Shape. It's 3d equivalent of a pixel.
    class Voxel
    {
    public:
        /// Default constructor
        /// \param [in] position - position of the voxel.
        /// \param [in] color - color of the voxel.
        VOXELIT_API Voxel(glm::tvec3<int32_t> position = glm::tvec3<int32_t>(), glm::vec3 color = glm::vec3());

        /// Gets position of the voxel.
        /// \return position of the voxel.
        const glm::tvec3<int32_t> VOXELIT_API getPosition() const;

        /// Sets position of the voxel.
        /// \param [in] position - position of the voxel.
        void VOXELIT_API setPosition(glm::tvec3<int32_t>& position);

        /// Gets color of the voxel.
        /// \return color of the voxel.
        const glm::vec3 VOXELIT_API getColor() const;

        /// Sets color of the voxel.
        /// \param [in] color - color of the voxel.
        void VOXELIT_API setColor(glm::vec3& color);

        /// Compares two voxel objects
        /// \param [in] other - second voxel object.
        /// \return true, if objects are the same, othervise false.
        bool VOXELIT_API operator==(const Voxel &other) const;
        
    private:
        glm::tvec3<int32_t> mPosition;
        glm::vec3 mColor;
    };
}

namespace std {
    /// Standard hash specialization for hashing Voxel object.
    template <>
    struct hash<vit::Voxel>
    {
        /// Hashes Voxel objects.
        /// \param [in] k - voxel object to be hashed.
        /// \return hash number representing voxel object.
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
