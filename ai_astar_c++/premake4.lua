-- ---------------------------------
-- Toni Barella, Gustavo Aranda
-- Inteligencia Artificial 3VGP
-- ESAT 2016-202X
-- Genie Project Configuration.
-- ---------------------------------

solution ("3IA_Solution" .. _ACTION)
  configurations { "Debug", "Release" }
  platforms { "x32", "x64" }
  location ("build")
  language "C"
  kind "ConsoleApp"

	language "C++"
	kind "ConsoleApp"

	projects = { "PR0_AI" }

	for i, prj in ipairs(projects) do
		project (prj)
		targetname (prj)

		prj_path = "./build/" .. prj

		location (prj_path .. "/" .. _ACTION)

		includedirs {
			"./deps/sfml/x86/include",
			"./deps/imgui-SFML/",
			"./deps/imgui/",
			"./include/",
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
		  }
      targetdir ("bin/Release")
      objdir ("build/" .. "Release")
      flags { "Optimize" }

	end

	project "PR0_AI"
		files { "./src/**.cc", "./include/**.h",
				"./deps/imgui-SFML/imgui-sfml.cpp",
				"./deps/imgui/imgui.cpp",
				"./deps/imgui/imgui_draw.cpp",
				"./deps/imgui/imgui_tables.cpp",
				"./deps/imgui/imgui_widgets.cpp",
				}
