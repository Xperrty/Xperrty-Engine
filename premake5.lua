workspace "Xperrty"
    architecture "x64"
    startproject "Sandbox"

configurations
{
    "Debug",
    "Release",
    "Dist"
}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir={}
IncludeDir["GLAD"] = "XperrtyEngine/vendor/GLAD/include"
IncludeDir["GLFW"] = "XperrtyEngine/vendor/GLFW/include"
IncludeDir["stb_image"] = "XperrtyEngine/vendor/stb_image"
include "XperrtyEngine/vendor/GLAD"
include "XperrtyEngine/vendor/GLFW"

project "XperrtyEngine"
    location "XperrtyEngine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "xppch.h"
    pchsource "XperrtyEngine/src/xppch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp"
    }

    links{
        "GLFW",
        "GLAD",
        "opengl32.lib"
    }

    includedirs{
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.stb_image}",
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "XP_PLATFORM_WINDOWS",
            "XP_BUILD_DLL",
            "GLFW_INCLUDE_NONE",
            "_CONSOLE",
            -- XP_PLATFORM_WINDOWS;XP_BUILD_DLL;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
            -- XP_PLATFORM_WINDOWS;XP_BUILD_DLL;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)
        }

        -- postbuildcommands
        -- {
        --     ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        -- }
    
        filter "configurations:Debug"
            defines "XP_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "XP_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "XP_DIST"
            optimize "On"

        -- filter {"system:windows","configurations:Release"}
        --     buildoptions: "/MT"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    links{
        "XperrtyEngine"
    }


    includedirs{
        "XperrtyEngine/vendor/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.GLAD}",
        "%{IncludeDir.stb_image}",
        "XperrtyEngine/src",
    }

    filter "system:windows"
        systemversion "latest"

        defines{
            "XP_PLATFORM_WINDOWS",
            "_CONSOLE",
            -- XP_PLATFORM_WINDOWS;XP_BUILD_DLL;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)
            -- XP_PLATFORM_WINDOWS;XP_BUILD_DLL;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)
        }
    
        filter "configurations:Debug"
            defines "XP_DEBUG"
            symbols "On"

        filter "configurations:Release"
            defines "XP_RELEASE"
            optimize "On"

        filter "configurations:Dist"
            defines "XP_DIST"
            optimize "On"

        -- filter {"system:windows","configurations:Release"}
        --     buildoptions: "/MT"