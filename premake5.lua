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

include "Renderer/3rdParty/GLFW"
include "Renderer/3rdParty/GLAD"
include "Renderer/3rdParty/imgui"

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
		"%{IncludeDir.stbimage}"
	}
	
	pchheader "stdafx.h"
    pchsource "%{prj.name}/Source/stdafx.cpp"
	
	ignoredefaultlibraries { "LIBCMTD" }
	
	links
	{
	    "GLFW",
		"GLAD",
	    "opengl32.lib",
		"imgui"
	}

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
		
		defines
		{
		    _DEBUG
		}

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"
	   