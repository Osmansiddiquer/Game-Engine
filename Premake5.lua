workspace "Game-Engine"
	architecture "x64"
	startproject "Sandbox"
	configurations 
	{
		"Debug", -- For Use while programming Game Engine
		"Release", -- For use while working with scripting in Game Engine
		"Dist" -- For use in final game distribution
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
IncludeDir = {} --structure
IncludeDir["GLFW"] = "Game-Engine/vendor/GLFW/include"
IncludeDir["Glad"] = "Game-Engine/vendor/Glad/include"
IncludeDir["imgui"] = "Game-Engine/vendor/imgui"

include "Game-Engine/vendor/GLFW/"
include "Game-Engine/vendor/Glad/"
include "Game-Engine/vendor/imgui"

project "Game-Engine"
	location "Game-Engine"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "Engine_pch.h"
	pchsource "Game-Engine/src/Engine_pch.cpp"


	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.imgui}"
	}
	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "Off"
		systemversion "latest"

		defines
		{
			"ENGINE_BUILD_DLL",
			"ENGINE_PLATFORM_WINDOWS"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/SandBox")
		}
	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		buildoptions "/MDd"
		symbols "On"
		optimize "On"
		runtime "Debug"


	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		symbols "On"
		optimize "On"
		runtime "Release"

	filter "configurations:Dist"
		defines "ENGINE_DIST"
		symbols "On"
		optimize "On"
		runtime "Release"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}") 
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Game-Engine/vendor/spdlog/include",
		"Game-Engine/src"
	}

	links
	{
		"Game-Engine"
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"ENGINE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "ENGINE_DEBUG"
		runtime "Debug"
		symbols "On"
		buildoptions "/MDd"

	filter "configurations:Release"
		defines "ENGINE_RELEASE"
		symbols "On"
		runtime "Release"
		buildoptions "/MD"

	filter "configurations:Dist"
		defines "ENGINE_DIST"
		symbols "On"
		runtime "Release"
		buildoptions "/MD"
