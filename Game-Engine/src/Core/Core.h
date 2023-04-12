#pragma once
//automating dll exporting and importing
#ifdef ENGINE_PLATFORM_WINDOWS //specific to windows
	#ifdef ENGINE_BUILD_DLL  //set different macros for import and exporsst
		#define ENGINE_API __declspec(dllexport)
	#else
		#define ENGINE_API __declspec(dllimport)
	#endif
#else
	#error Engine only supports windows at the moment
#endif

//Assertions

#ifdef ENGINE_DEBUG
#define ASSERT(expr, description) \
if (expr) { } \
else \
{ \
	ENGINE_CORE_ERROR("Asssertion: {0} failed ---- File: {1} | Line: {2}", description, \
	__FILE__, __LINE__); \
	__debugbreak(); \
}
#else
#define ASSERT(expr, description) //evaluates to nothing
#endif

struct Vec2 { double x = 0, y = 0; };
struct Vec3 { double x = 0, y = 0, z = 0; };
struct Vec4 { double x = 0, y = 0, z = 0, w = 0; };
