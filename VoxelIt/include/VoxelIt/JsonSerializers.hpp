#pragma once
#include <VoxelIt/Prerequisites.hpp>
#include <VoxelIt/Vertex.hpp>
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
}
