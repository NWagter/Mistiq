workspace "Mistiq"
	architecture "x64"

	configurations { 
	"Debug", 
	"Release" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Mistiq/vendor/GLFW"
IncludeDir["Glad"] = "Mistiq/vendor/Glad"
IncludeDir["ImGui"] = "Mistiq/vendor/imgui"
IncludeDir["Optick"] = "Mistiq/vendor/Optick/include"

group "Dependencies"
	include "Mistiq/vendor/GLFW"
	include "Mistiq/vendor/Glad"
	include "Mistiq/vendor/imgui"
group ""

project "Mistiq"
	location "Mistiq"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

 	pchheader "Mstqpch.h"
	pchsource "Mistiq/src/Mstqpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/src/",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLFW}/include/GLFW",
		"%{IncludeDir.Optick}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"OptickCore.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MSTQ_PLATFORM_WINDOWS",
			"MSTQ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MSTQ_DEBUG"
		symbols "On"

		libdirs { 
			"Mistiq/vendor/Optick/lib/x64/debug"
		}

	filter "configurations:Release"
		defines "MSTQ_RELEASE"
		optimize "On"

		libdirs { 
			"Mistiq/vendor/Optick/lib/x64/release"
		}

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Mistiq/src",
		"%{IncludeDir.Optick}"
	}

	links {
		"Mistiq"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MSTQ_PLATFORM_WINDOWS"
		}

		postbuildcommands 
		{
			"{COPY} %{cfg.targetdir}/../Mistiq/Mistiq.dll %{cfg.targetdir}"
		}

	filter "configurations:Debug"
		defines "MSTQ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MSTQ_RELEASE"
		optimize "On"