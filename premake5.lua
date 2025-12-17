workspace("FinalRayTracing")
	configurations({"DEBUG","RELEASE"})

project "FinalRayTracing"
   kind "ConsoleApp"
   language "C++"
   --cppstandard "C++20"
   targetdir "bin/%{cfg.buildcfg}"

   files({ 	"./lib/math/**.h","./lib/math/**.cpp",
   			"./renderer/**.h", "./renderer/**.cpp",
			"./main/**.cpp" 
		})

   filter "configurations:Debug"
      defines { "DEBUG" }
      symbols "On"
      optimize "Off"

   filter "configurations:Release"
      defines { "NDEBUG" }
      optimize "On"

