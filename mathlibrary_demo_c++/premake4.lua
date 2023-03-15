-- ---------------------------------
-- Toni Barella, Gustavo Aranda
-- ESAT 2016-202X
-- Genie Project Configuration.
-- ---------------------------------

solution ("2PA_Solution" .. _ACTION)
  configurations { "Debug", "Release" }
  platforms { "x32", "x64" }
  location ("build")
  language "C"
  kind "ConsoleApp"

	language "C++"
	kind "ConsoleApp"

	projects = { "PR1_Test", "PR2_Demo" }

	for i, prj in ipairs(projects) do
		project (prj)
		targetname (prj)

		prj_path = "./build/" .. prj

		location (prj_path .. "/" .. _ACTION)

		includedirs {
			"./deps/sfml/x86/include",
			"./deps/imgui-SFML",
			"./deps/imgui",
     		"./include",
     		"./include/math_library", "./include/math_library/vector", "./include/math_library/matrix",
			"./include/unit_test",
			"./data",
			"./deps/data_structure/include",
			"./deps/data_structure/include/ABGS_MemoryManager",
			"./include/data_structure", "./src/data_structure",
		}

		--files {
		--	"./include/*.h",
		--}

	  defines { "_CRT_SECURE_NO_WARNINGS" }
	  flags { "ExtraWarnings" }

		configuration "vs2015"
		  windowstargetplatformversion "8.1"

		configuration "vs2017"
		--windowstargetplatformversion "10.0.15063.0"
		--windowstargetplatformversion "10.0.16299.0"
		windowstargetplatformversion "10.0.17134.0"
		--windowstargetplatformversion "10.0.17134.471"


    configuration "Debug"
      defines { "DEBUG" }
		  links { "./deps/sfml/x86/lib/sfml-graphics-d",
		  "./deps/sfml/x86/lib/sfml-window-d",
		  "./deps/sfml/x86/lib/sfml-system-d",
		  "./deps/data_structure/lib/ABGS_MemoryManager/ABGS_MemoryManager_w32d",
		  "opengl32", "user32","shell32","gdi32"
		  }
      targetdir ("bin/Debug")
      targetsuffix "_d"
      objdir ("build/" .. "Debug")
      flags { "Symbols" }

    configuration "Release"
		  links { "./deps/sfml/x86/lib/sfml-graphics",
				  "./deps/sfml/x86/lib/sfml-window",
				  "./deps/sfml/x86/lib/sfml-system",
				  "./deps/data_structure/lib/ABGS_MemoryManager/ABGS_MemoryManager_w32",
				  "opengl32", "user32","shell32","gdi32"
		  }
      targetdir ("bin/Release")
      objdir ("build/" .. "Release")
      flags { "Optimize" }

	end


	project "PR1_Test"
		files { "./include/math_library/**.h", "./include/math_library/vector/**.h", "./include/math_library/matrix/**.h",
			  	"./src/math_library/vector/**.cc", "./src/math_library/matrix/**.cc",
				  "./include/unit_test/**.h",
			 	 "./src/unit_test/**.cpp",
	 	}

	project "PR2_Demo"
		files { "./include/math_library/**.h", "./include/math_library/vector/**.h", "./include/math_library/matrix/**.h",
		     	"./src/math_library/vector/**.cc", "./src/math_library/matrix/**.cc",
				"./deps/imgui-SFML/**.cpp", "./deps/imgui/**.cpp",
				"./deps/data_structure/include/**.h", "./deps/data_structure/include/ABGS_MemoryManager/**.h",
				"./include/data_structure/adt_memory_node.h", "./src/data_structure/adt_memory_node.c",
				"./include/data_structure/adt_vector.h", "./src/data_structure/adt_vector.c",
				"./src/**.cc", "./src/**.c", "./include/**.h"
		}
