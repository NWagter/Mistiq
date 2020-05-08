workspace "Mistiq"
	architecture "x64"

	configurations { 
	"Debug", 
	"Release" 
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Mistiq/ext/GLFW"
IncludeDir["Glad"] = "Mistiq/ext/Glad"
IncludeDir["ImGui"] = "Mistiq/ext/ImGui"
IncludeDir["Optick"] = "Mistiq/ext/Optick/include"

group "Dependencies"
	include "Mistiq/ext/GLFW"
	include "Mistiq/ext/Glad"
	include "Mistiq/ext/imgui"
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

		postbuildcommands
		{
			--'"xcopy $(SolutionDir)\\bin\\Debug-windows-x86_64\\Mistiq\\Mistiq.lib $(SolutionDir)\\bin\\Debug-windows-x86_64\\Sandbox /d /s /i",
			--"xcopy $(SolutionDir)\\Mistiq\\ext\\Optick\\lib\\x64\\debug\\OptickCore.dll $(SolutionDir)\\bin\\Debug-windows-x86_64\\Sandbox /d /s /i"
		}

	filter "configurations:Debug"
		defines "MSTQ_DEBUG"
		symbols "On"

		libdirs { 
			"Mistiq/ext/Optick/lib/x64/debug"
		}

	filter "configurations:Release"
		defines "MSTQ_RELEASE"
		optimize "On"

		libdirs { 
			"Mistiq/ext/Optick/lib/x64/release"
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

	filter "configurations:Debug"
		defines "MSTQ_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MSTQ_RELEASE"
		optimize "On"