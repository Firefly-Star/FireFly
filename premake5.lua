workspace "FireFly"
	architecture "x64"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	startproject "Sandbox"
	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLFW"] = "FireFly/vendor/GLFW/src/glfw-3.4/include"
	IncludeDir["Glad"] = "FireFly/vendor/Glad/include"
	IncludeDir["ImGui"] = "FireFly/vendor/ImGui"
	IncludeDir["GLM"] = "FireFly/vendor/GLM/glm-master"

	include "FireFly/vendor/GLFW/src/glfw-3.4"
	include "FireFly/vendor/Glad"
	include "FireFly/vendor/ImGui"

--------------------------------------------------------------------------------

	project "FireFly"

		location "FireFly"
		kind "SharedLib"
		language "C++"
		staticruntime "Off"

		targetdir ("bin/" .. outputdir .. "/%{ prj.name }")
		objdir ("bin-int/" .. outputdir .. "/%{ prj.name }")

		pchheader "ffpch.h"
		pchsource "%{prj.name}/src/ffpch.cpp"

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/vendor/GLM/glm-master/glm/**.hpp",
			"%{prj.name}/vendor/GLM/glm-master/glm/**.inl"
		}

		includedirs
		{
			"%{prj.name}/src",
			"%{prj.name}/vendor/spdlog/include",
			"%{IncludeDir.GLFW}",
			"%{IncludeDir.Glad}",
			"%{IncludeDir.ImGui}",
			"%{IncludeDir.ImGui}/backends",
			"%{IncludeDir.GLM}"
		}

		links
		{
			"GLFW",
			"opengl32.lib",
			"Glad",
			"ImGui"
		}

		defines
		{
			"GLFW_INCLUDE_NONE"
		}

		
		filter "system:windows"
			cppdialect "C++17"
			systemversion "latest"
		
			defines
			{
				"FF_PLATFORM_WINDOWS",
				"FF_BUILD_DLL"
			}
		
		
			local copycommand = "{COPYFILE} %[bin/" .. outputdir .. "/%{prj.name}/%{prj.name}.dll] %[bin/" .. outputdir.. "/Sandbox/]"
			
			postbuildcommands
			{
				--"{COPYFILE} %[bin\\Debug-windows-x86_64\\FireFly\\FireFly.dll] %[bin\\Debug-windows-x86_64\\Sandbox\\]"
				copycommand
			}
		
		filter "configurations:Debug"
			defines "FF_DEBUG"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			defines "FF_DEBUG"
			optimize "On"
			runtime "Release"

		filter "configurations:Debug"
			defines "FF_DEBUG"
			optimize "Full"
			runtime "Release"
------------------------------------------------------------------------

	project "Sandbox"

		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		staticruntime "Off"

		targetdir ("bin/" .. outputdir .. "/%{ prj.name }")
		objdir ("bin-int/" .. outputdir .. "/%{ prj.name }")

		files
		{
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp"
		}

		includedirs
		{
			"FireFly/vendor/spdlog/include",
			"FireFly/src",
			"%{IncludeDir.GLM}"
		}

		links
		{
			"FireFly"
		}

		filter "system:windows"
			cppdialect "C++17"
			systemversion "latest"

			defines
			{
				"FF_PLATFORM_WINDOWS",
			}

		filter "configurations:Debug"
			defines "FF_DEBUG"
			symbols "On"
			runtime "Debug"

		filter "configurations:Release"
			defines "FF_DEBUG"
			optimize "On"
			runtime "Release"

		filter "configurations:Debug"
			defines "FF_DEBUG"
			optimize "Full"
			runtime "Release"

----------------------------------------------------------------------------