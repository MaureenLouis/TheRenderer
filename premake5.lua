workspace "TheRenderer"
   architecture "x64"
   configurations 
   { 
       "Debug", 
	   "Release"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder
IncludeDir = {}
IncludeDir["GLFW"]   = "Renderer/3rdParty/GLFW/include"
IncludeDir["GLAD"]   = "Renderer/3rdParty/GLAD/include"
IncludeDir["glm"]    = "Renderer/3rdParty/glm"
IncludeDir["tabula"] = "Renderer/3rdParty/tabulate/include"
IncludeDir["spdlog"] = "Renderer/3rdParty/spdlog/include"
IncludeDir["imgui"]  = "Renderer/3rdParty/imgui"
IncludeDir["stbimage"] = "Renderer/3rdParty/stbimage/include"
IncludeDir["assimp"] = "Renderer/3rdParty/assimp/include"
IncludeDir["entt"]   = "Renderer/3rdParty/entt"

include "Renderer/3rdParty/GLFW"
include "Renderer/3rdParty/GLAD"
include "Renderer/3rdParty/imgui"
include "Renderer/3rdParty/assimp"

project "Renderer"
    location "Renderer"
    kind "ConsoleApp"
    language "C++"
    
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir    ("int/" .. outputdir .. "/%{prj.name}")

    files 
	{ 
	    "%{prj.name}/Source/**.h", 
		"%{prj.name}/Source/**.cpp"
	}
	
	includedirs
	{
	    "%{prj.name}/Source",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.GLAD}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stbimage}",
		"%{IncludeDir.assimp}",
		"%{IncludeDir.entt}"
	}
	
	pchheader "stdafx.h"
    pchsource "%{prj.name}/Source/stdafx.cpp"
	
	ignoredefaultlibraries { "LIBCMTD" }
	


    filter "system:windows"
	    cppdialect    "C++17"
		systemversion "latest"
		 
		defines
		{
		    "_CRT_SECURE_NO_WARNINGS",
            "GLM_FORCE_SSE2",
            "GLM_FORCE_ALIGNED"
		}
		
		postbuildcommands
		{
		
		}
		
    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"
		staticruntime "on"
		runtime "Debug"
		
		defines
		{
		    _DEBUG
		}
		
	links
	{
		"assimp",
	    "GLFW",
		"GLAD",
	    "opengl32.lib",
		"imgui",
		"Pathcch.lib",
        "msvcrtd.lib"
	}

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"
	    staticruntime "on"
		runtime "Release"
		
			links
	{
		"assimp",
	    "GLFW",
		"GLAD",
	    "opengl32.lib",
		"imgui",
		"Pathcch.lib",
        "msvcrt.lib"
	}