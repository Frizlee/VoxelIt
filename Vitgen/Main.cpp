#include <iostream>
#include <VoxelIt/Mesh.hpp>
#include <VoxelIt/Vertex.hpp>
#include <VoxelIt/JsonSerializers.hpp>
#include <nlohmann/json.hpp>
using nlohmann::json;

int main(int argc, char **argv)
{
    vit::Mesh m;
    vit::Vertex simpleVertex({ 1.0f, 0.0f, 1.0f });

    json j = simpleVertex;

    std::cout << std::setw(4) << j << std::endl;

    return 0;
}