cmake_minimum_required(VERSION 3.8)
project(GalaxyRenderer)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_TTF REQUIRED)
find_package(GLEW REQUIRED)

#set(OPENGL_glx_LIBRARY)
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(LIB_SRC_FILES
   CumulativeDistributionFunction.cpp 
   Galaxy.cpp 
   GalaxyWnd.cpp 
   Helper.cpp  
   SDLWnd.cpp 
   TextBuffer.cpp
)

set(GALAXY_RENDERER_HEADERS
   include/CumulativeDistributionFunction.hpp 
   include/Galaxy.hpp 
   include/GalaxyWnd.hpp 
   include/Helper.hpp  
   include/SDLWnd.hpp 
   include/TextBuffer.hpp
   include/Types.hpp
   include/VertexBufferBase.hpp
   include/VertexBufferLines.hpp
   include/VertexBufferStars.hpp
)

set(EXE_SRC_FILES
   main.cpp
)

add_library(galaxy_renderer SHARED)
target_sources(galaxy_renderer PRIVATE
    ${LIB_SRC_FILES}
    ${GALAXY_RENDERER_HEADERS}
)
target_include_directories(galaxy_renderer PRIVATE
    include
)
target_include_directories(galaxy_renderer PUBLIC 
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>/galaxy_renderer)
target_include_directories(galaxy_renderer SYSTEM
  PUBLIC ${SDL2_INCLUDE_DIR}
)
target_link_libraries(galaxy_renderer
    ${SDL2_LIBRARY} 
    GLEW::GLEW 
    ${OPENGL_LIBRARIES} 
    ${SDL2_TTF_LIBRARY}
)
set_target_properties(galaxy_renderer PROPERTIES PUBLIC_HEADER "${GALAXY_RENDERER_HEADERS}")

add_executable(galaxy_renderer_gui)
target_sources(galaxy_renderer_gui PRIVATE
    ${EXE_SRC_FILES}
)
target_include_directories(galaxy_renderer_gui PRIVATE
    include
)
target_link_libraries(galaxy_renderer_gui
    galaxy_renderer
)

install(TARGETS 
    galaxy_renderer
    galaxy_renderer_gui
    EXPORT galaxy_rendererConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION include/galaxy_renderer
)

export(TARGETS galaxy_renderer
    NAMESPACE galaxy_renderer::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/galaxy_rendererConfig.cmake"
)

install(EXPORT galaxy_rendererConfig
    DESTINATION "${CMAKE_INSTALL_DATADIR}/galaxy_renderer/cmake"
    NAMESPACE galaxy_renderer::
)