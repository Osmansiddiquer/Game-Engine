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