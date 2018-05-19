#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
#include <VoxelIt/Voxel.hpp>
#include <glm/vec3.hpp>
#include <nlohmann/json.hpp>

namespace glm
{
    void to_json(nlohmann::json& j, const vec3& vec)
    {
        j = nlohmann::json{ { "x", vec.x }, { "y", vec.y }, { "z", vec.z } };
    }

    void from_json(const nlohmann::json& j, vec3& vec)
    {
        vec.x = j.at("x").get<vec3::value_type>();
        vec.y = j.at("y").get<vec3::value_type>();
        vec.z = j.at("z").get<vec3::value_type>();
    }

    void to_json(nlohmann::json& j, const tvec3<int32_t>& vec)
    {
        j = nlohmann::json{ { "x", vec.x }, { "y", vec.y }, { "z", vec.z } };
    }

    void from_json(const nlohmann::json& j, tvec3<int32_t>& vec)
    {
        vec.x = j.at("x").get<vec3::value_type>();
        vec.y = j.at("y").get<vec3::value_type>();
        vec.z = j.at("z").get<vec3::value_type>();
    }
}

namespace vit
{
    void to_json(nlohmann::json& j, const Vertex& vertex)
    {
        j = nlohmann::json{ { "position", vertex.getPosition() }, { "color", vertex.getColor() }, { "normal", vertex.getNormal() } };
    }

    void from_json(const nlohmann::json& j, Vertex& vertex)
    {
        auto position = j.at("position").get<glm::vec3>();
        auto color = j.at("color").get<glm::vec3>();
        auto normal = j.at("normal").get<glm::vec3>();

        vertex.setPosition(position);
        vertex.setColor(color);
        vertex.setNormal(normal);
    }

    void to_json(nlohmann::json& j, const Voxel& voxel)
    {
        j = nlohmann::json{ { "position", voxel.getPosition() }, { "color", voxel.getColor() } };
    }

    void from_json(const nlohmann::json& j, Voxel& voxel)
    {
        auto position = j.at("position").get<glm::tvec3<int32_t>>();
        auto color = j.at("color").get<glm::vec3>();

        voxel.setPosition(position);
        voxel.setColor(color);
    }
}
