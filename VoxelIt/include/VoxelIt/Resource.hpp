#pragma once
#include <VoxelIt/Prerequisites.hpp>

namespace vit
{
    class Resource
    {
    public:
        VOXELIT_API Resource();
        virtual VOXELIT_API ~Resource() = 0;
    };
}
