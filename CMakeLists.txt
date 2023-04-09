cmake_minimum_required(VERSION 3.8)
project(GalaxyRenderer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(GNUInstallDirs)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#set(OPENGL_glx_LIBRARY)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
find_package( GLUT REQUIRED)
find_package( GLEW   REQUIRED )
find_package( OpenGL REQUIRED)

QT5_WRAP_UI(QT_GL_WINDOW_UISrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/src/qtglwindow.ui
)

set(QT_GL_WIDGET_SRC
  src/QtGlWidget.cpp
  include/QtGlWidget.hpp
)

set(QT_GL_WINDOW_SRC
  src/QtGlWindow.cpp
  include/QtGlWindow.hpp
)

set(QT_MAIN_SRC
  src/main_qt.cpp 
)

QT5_WRAP_CPP(QT_GL_WINDOW_MOCrcs
  ${QT_GL_WINDOW_SRC}
)

QT5_WRAP_CPP(QT_GL_WIDGET_MOCrcs
  ${QT_GL_WIDGET_SRC}
)

QT5_WRAP_CPP(QT_MAIN_MOCrcs
  ${QT_MAIN_SRC}
)

set(LIB_SRC_FILES
 src/CumulativeDistributionFunction.cpp 
 src/Galaxy.cpp 
# src/GalaxyWnd.cpp 
 src/Helper.cpp 
 src/TextBuffer.cpp
)

set(GALAXY_RENDERER_HEADERS
   include/CumulativeDistributionFunction.hpp 
   include/Galaxy.hpp 
   include/GalaxyWnd.hpp 
   include/Helper.hpp  
#   include/SDLWnd.hpp 
   include/TextBuffer.hpp
   include/Types.hpp
   include/VertexBufferBase.hpp
   include/VertexBufferLines.hpp
   include/VertexBufferStars.hpp
)

set(EXE_SRC_FILES
  src/main.cpp 
)

add_library(qt_gl_window)
target_sources(qt_gl_window
  PRIVATE
  ${QT_GL_WINDOW_SRC}
  ${QT_GL_WINDOW_UISrcs}
  ${QT_GL_WINDOW_MOCrcs}
  ${QT_GL_Widget_SRC_FILES}
  ${QT_GL_Widget_UISrcs}
  ${QT_GL_Widget_MOCrcs}
)
target_include_directories(qt_gl_window PRIVATE include)
target_include_directories(qt_gl_window PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(qt_gl_window SYSTEM
  PUBLIC
  ${Qt5Core_INCLUDE_DIRS}
  ${Qt5Widgets_INCLUDE_DIRS}
)
target_link_libraries(qt_gl_window PRIVATE
  Qt5::Core
  Qt5::Widgets
)

#add_library(galaxy_renderer SHARED)
#target_sources(galaxy_renderer PRIVATE
#    ${LIB_SRC_FILES}
#    ${GALAXY_RENDERER_HEADERS}
#)
#target_include_directories(galaxy_renderer PRIVATE
#    include
#)
#target_include_directories(galaxy_renderer PUBLIC
#  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>/galaxy_renderer)
#target_include_directories(galaxy_renderer SYSTEM
#  PUBLIC ${SDL2_INCLUDE_DIR}
#)
#target_link_libraries(galaxy_renderer
#    ${SDL2_LIBRARY}
#    GLEW::GLEW
#    ${OPENGL_LIBRARIES}
#    ${SDL2_TTF_LIBRARY}
#)
#set_target_properties(galaxy_renderer PROPERTIES PUBLIC_HEADER "${GALAXY_RENDERER_HEADERS}")

#add_executable(galaxy_renderer_gui)
#target_sources(galaxy_renderer_gui PRIVATE
#    ${EXE_SRC_FILES}
#)
#target_include_directories(galaxy_renderer_gui PRIVATE
#    include
#)
#target_link_libraries(galaxy_renderer_gui
#    galaxy_renderer
#)

add_executable(qt_galaxy_renderer_gui)
target_sources(qt_galaxy_renderer_gui PRIVATE
	${QT_MAIN_MOCrcs}
  ${QT_MAIN_SRC}
	)
target_include_directories(qt_galaxy_renderer_gui PRIVATE
    include
)
target_link_libraries(qt_galaxy_renderer_gui
  #galaxy_renderer
	qt_gl_window
	Qt5::OpenGL
)


install(TARGETS 
#  galaxy_renderer
#  galaxy_renderer_gui
  qt_galaxy_renderer_gui
  EXPORT galaxy_rendererConfig
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  PUBLIC_HEADER DESTINATION include/galaxy_renderer
)

#export(TARGETS galaxy_renderer
#    NAMESPACE galaxy_renderer::
#    FILE "${CMAKE_CURRENT_BINARY_DIR}/galaxy_rendererConfig.cmake"
#)

#install(EXPORT galaxy_rendererConfig
#    DESTINATION "${CMAKE_INSTALL_DATADIR}/galaxy_renderer/cmake"
#    NAMESPACE galaxy_renderer::
#)
