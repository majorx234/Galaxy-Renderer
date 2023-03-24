cmake_minimum_required(VERSION 3.8)
project(GalaxyRenderer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(GLEW REQUIRED)

#set(OPENGL_glx_LIBRARY)
set(OpenGL_GL_PREFERENCE GLVND)
#OPENGL_opengl_LIBRARY)
find_package(OpenGL REQUIRED)

message(STATUS "sdl include: ${SDL2_INCLUDE_DIR} ${SDL2_TTF_INCLUDE_DIR}" )
message(STATUS "sdl libs: ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY}")


include_directories(
	include
	${SDL2_INCLUDE_DIR}
	)

set(SRC_FILES
 CumulativeDistributionFunction.cpp 
 Galaxy.cpp 
 GalaxyWnd.cpp 
 Helper.cpp 
 main.cpp 
 SDLWnd.cpp 
 TextBuffer.cpp
)

add_executable(galaxy_rendere ${SRC_FILES} )
target_link_libraries(galaxy_rendere ${SDL2_LIBRARY} GLEW::GLEW ${OPENGL_LIBRARIES} ${SDL2_TTF_LIBRARY})
