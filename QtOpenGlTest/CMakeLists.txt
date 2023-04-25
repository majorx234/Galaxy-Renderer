cmake_minimum_required(VERSION 3.8)
PROJECT(QtTestGalaxy)

set(OpenGL_GL_PREFERENCE GLVND)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_package( GLUT REQUIRED)
find_package( GLEW   REQUIRED )
find_package( OpenGL REQUIRED)
#set(CMAKE_AUTORCC ON)

list (APPEND RESOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc
)
qt5_add_resources (RCC_SOURCES ${RESOURCES})

set(MAIN_OPENGL_WINDOW_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# 1st approach OpenGL window
set(OPENGL_WINDOW_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl_window.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_window.hpp
)

QT5_WRAP_CPP( OPENGL_WINDOW_MOC_SOURCES
  ${OPENGL_WINDOW_SOURCES}
)

# 2nd Approach OpenGL widget
set(OPENGL_WIDGET_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/opengl_widget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/opengl_widget.hpp
)

QT5_WRAP_CPP( OPENGL_WIDGET_MOC_SOURCES
  ${OPENGL_WIDGET_SOURCES}
)

set(MAIN_OPENGL_WINDOW_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_opengl_window_test.cpp
)

QT5_WRAP_CPP(MAIN_WINDOW_MOCsrcs
  {MAIN_OPENGL_WINDOW_TEST_SOURCES}
)

set(MAIN_OPENGL_WIDGET_TEST_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main_opengl_widget_test.cpp
)

QT5_WRAP_CPP(MAIN_WIDGET_MOCsrcs
  {MAIN_OPENGL_WIDGET_TEST_SOURCES}
)

set(GALAXY_RENDERER_HEADERS
   ../include/CumulativeDistributionFunction.hpp 
   ../include/Galaxy.hpp 
   ../include/Helper.hpp  
   ../include/TextBuffer.hpp
   ../include/Types.hpp
   ../include/VertexBufferBase.hpp
   ../include/VertexBufferLines.hpp
   ../include/VertexBufferStars.hpp
)

set(GALAXY_RENDERER_SRC
	../src/Galaxy.cpp
	../src/CumulativeDistributionFunction.cpp
	../src/TextBuffer.cpp
	)

add_library(galaxy_lib)
target_sources(galaxy_lib
	PRIVATE
	${GALAXY_RENDERER_SRC}
	)
target_include_directories(galaxy_lib PUBLIC ../include)

add_library(opengl_widget SHARED)
target_sources(opengl_widget
 PRIVATE
  ${OPENGL_WIDGET_SOURCES}
  ${OPENGL_WIDGET_MOC_SOURCES}
)
target_include_directories(opengl_widget
 PRIVATE
  include
)
target_link_libraries(opengl_widget
  ${OpenCV_LIBS}
  ${OPENGL_LIBRARIES}
  ${GLUT_LIBRARY}
  GLEW::GLEW
  Qt5::Core
  Qt5::Widgets
)

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

add_executable(qtopengl_widget_test)
target_sources(qtopengl_widget_test
  PRIVATE
  ${MAIN_OPENGL_WIDGET_TEST_MOC_SOURCES}
  ${MAIN_OPENGL_WIDGET_TEST_SOURCES}
)
target_include_directories(qtopengl_widget_test
 PUBLIC
  ${Qt5Core_INCLUDE_DIRS}
 PRIVATE
  include
)
target_link_libraries(qtopengl_widget_test
  opengl_widget
  Qt5::Core
  Qt5::Widgets
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
