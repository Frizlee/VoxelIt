#pragma once

#ifdef VOXELIT_DLL_EXPORT
#define VOXELIT_API _declspec(dllexport)
#else
#ifdef VOXELIT_STATIC
#define VOXELIT_API
#else
#define VOXELIT_API _declspec(dllimport)
#endif
#endif
