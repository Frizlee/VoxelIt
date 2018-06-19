#pragma once
#include <VoxelIt/Prerequisites.hpp>

namespace vit
{
    /// Base abstract resource class.
    class Resource
    {
    public:
        /// Default constructor.
        VOXELIT_API Resource();

        /// Virtual destructor which also defines this class as abstract class.
        virtual VOXELIT_API ~Resource() = 0;
    };
}
