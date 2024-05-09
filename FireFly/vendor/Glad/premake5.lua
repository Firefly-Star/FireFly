project "Glad"
    language "C"
    kind "StaticLib"

    targetdir ("bin/"..outputdir.."/%{prj.name}")
    objdir ("bin-int/"..outputdir.."/%{prj.name}")

    includedirs
    {
        "include"
    }

    files
    {
        "**.*"
    }

    filter "system:windows"
        staticruntime "On"
        systemversion "latest"