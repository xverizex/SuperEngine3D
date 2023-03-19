if (LINUX)
	include(FindPkgConfig)
	pkg_check_modules(GL gl)
	pkg_check_modules(SDL sdl2)

	set(SGL_INCLUDES ${GL_INCLUDE_DIRS})
	set(SGL_LIBS ${GL_LIBRARIES})

	set(SSDL_INCLUDES ${SDL_INCLUDE_DIRS})
	set(SSDL_LIBS ${SDL_LIBRARIES})
endif()
if (MSVC)
	set(SGL_INCLUDES "")
	set(SGL_LIBS OpenGL32)

	set(SSDL_INCLUDES ../SDL2/)
	set(SSDL_LIBS 
		SDL2
		SDL2main
		)

	link_directories(..)
	set(SGLM_INCLUDES ../glm)
endif()

set(ENGINE_SOURCES
	Engine/Core/main.cpp
	glad/src/glad.c
	Engine/Core/object.cpp
	Engine/Shaders/shader_pbr_with_shadows.cpp
	Engine/Shaders/shader_particle_system.cpp
	Engine/Shaders/shader_3d_simple.cpp
	Engine/Shaders/shader_2d_simple.cpp
	Engine/Core/shaders.cpp
	Engine/Core/downloader.cpp
	Engine/Core/camera.cpp
	Engine/Core/light.cpp
	Engine/Core/sun.cpp
	Engine/Core/timer.cpp
	Engine/Core/animation.cpp
	Engine/Core/particle.cpp
	)

set(GAME_SOURCES
	)

add_executable(${name_project} ${ENGINE_SOURCES} ${GAME_SOURCES})

target_include_directories(${name_project} PUBLIC  ${SGL_INCLUDES} ${SSDL_INCLUDES} ${SGLM_INCLUDES} glad/include Engine/include Game/include)

target_link_libraries(${name_project} PUBLIC ${SGL_LIBS} ${SSDL_LIBS})

set(EXECUTABLE_OUTPUT_PATH ..)
