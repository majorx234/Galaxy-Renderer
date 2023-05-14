cmake_minimum_required(VERSION 3.8)
PROJECT(QtTestGalaxy)

set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_package( GLUT REQUIRED)
find_package( GLEW   REQUIRED )
find_package( OpenGL REQUIRED)
#set(CMAKE_AUTORCC ON)

qt5_add_resources (RCC_SOURCES ${RESOURCES})

# 1st approach OpenGL window
set(OPENGL_WINDOW_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl_window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_window.hpp
)

QT5_WRAP_CPP( OPENGL_WINDOW_MOC_SOURCES
  ${OPENGL_WINDOW_SOURCES}
)

set(MAIN_OPENGL_WINDOW_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_opengl_window_test.cpp
)

QT5_WRAP_CPP(MAIN_WINDOW_MOCsrcs
  {MAIN_OPENGL_WINDOW_TEST_SOURCES}
)

set(GALAXY_RENDERER_HEADERS
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/CumulativeDistributionFunction.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/Galaxy.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/Helper.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/TextBuffer.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/Types.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/VertexBufferBase.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/VertexBufferLines.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/VertexBufferStars.hpp
)

set(GALAXY_RENDERER_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/src/galaxy_gl_lib/Galaxy.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/galaxy_gl_lib/CumulativeDistributionFunction.cpp
	)

add_library(galaxy_lib)
target_sources(galaxy_lib
	PRIVATE
	${GALAXY_RENDERER_SRC}
	)
target_include_directories(galaxy_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/galaxy_gl_lib/)

add_library(opengl_window)
target_sources(opengl_window
 PRIVATE
  ${OPENGL_WINDOW_SOURCES}
  ${OPENGL_WINDOW_MOC_SOURCES}
  ${RCC_SOURCES}
)
target_include_directories(opengl_window
 PUBLIC
  include
)
target_link_libraries(opengl_window
  ${OpenCV_LIBS}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
  GLEW::GLEW
  Qt5::Core
  Qt5::Widgets
  galaxy_lib
)


add_executable(qtopengl_window_test)
target_sources(qtopengl_window_test
  PRIVATE
  ${MAIN_OPENGL_WINDOW_TEST__MOC_SOURCES}
  ${MAIN_OPENGL_WINDOW_TEST_SOURCES}
)
target_include_directories(qtopengl_window_test
 PUBLIC
  ${Qt5Core_INCLUDE_DIRS}
 PRIVATE
  include
)
target_link_libraries(qtopengl_window_test
  opengl_window
  Qt5::Core
  Qt5::Widgets
)
