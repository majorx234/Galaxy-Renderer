# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build

# Include any dependencies generated for this target.
include CMakeFiles/opengl_widget.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/opengl_widget.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/opengl_widget.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/opengl_widget.dir/flags.make

src/moc_opengl_widget.cpp: /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/src/opengl_widget.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating src/moc_opengl_widget.cpp"
	cd /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/src && /usr/bin/moc @/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/src/moc_opengl_widget.cpp_parameters

include/moc_opengl_widget.cpp: /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/include/opengl_widget.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Generating include/moc_opengl_widget.cpp"
	cd /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/include && /usr/bin/moc @/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/include/moc_opengl_widget.cpp_parameters

CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o: CMakeFiles/opengl_widget.dir/flags.make
CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o: /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/src/opengl_widget.cpp
CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o: CMakeFiles/opengl_widget.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o -MF CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o.d -o CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o -c /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/src/opengl_widget.cpp

CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.i"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/src/opengl_widget.cpp > CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.i

CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.s"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/src/opengl_widget.cpp -o CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.s

CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o: CMakeFiles/opengl_widget.dir/flags.make
CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o: src/moc_opengl_widget.cpp
CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o: CMakeFiles/opengl_widget.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o -MF CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o.d -o CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o -c /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/src/moc_opengl_widget.cpp

CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.i"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/src/moc_opengl_widget.cpp > CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.i

CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.s"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/src/moc_opengl_widget.cpp -o CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.s

CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o: CMakeFiles/opengl_widget.dir/flags.make
CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o: include/moc_opengl_widget.cpp
CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o: CMakeFiles/opengl_widget.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o -MF CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o.d -o CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o -c /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/include/moc_opengl_widget.cpp

CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.i"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/include/moc_opengl_widget.cpp > CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.i

CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.s"
	/sbin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/include/moc_opengl_widget.cpp -o CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.s

# Object files for target opengl_widget
opengl_widget_OBJECTS = \
"CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o" \
"CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o" \
"CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o"

# External object files for target opengl_widget
opengl_widget_EXTERNAL_OBJECTS =

libopengl_widget.so: CMakeFiles/opengl_widget.dir/src/opengl_widget.cpp.o
libopengl_widget.so: CMakeFiles/opengl_widget.dir/src/moc_opengl_widget.cpp.o
libopengl_widget.so: CMakeFiles/opengl_widget.dir/include/moc_opengl_widget.cpp.o
libopengl_widget.so: CMakeFiles/opengl_widget.dir/build.make
libopengl_widget.so: /usr/lib/libOpenGL.so
libopengl_widget.so: /usr/lib/libGLX.so
libopengl_widget.so: /usr/lib/libGLU.so
libopengl_widget.so: /usr/lib/libGLEW.so
libopengl_widget.so: /usr/lib/libQt5Widgets.so.5.15.9
libopengl_widget.so: /usr/lib/libQt5Gui.so.5.15.9
libopengl_widget.so: /usr/lib/libQt5Core.so.5.15.9
libopengl_widget.so: CMakeFiles/opengl_widget.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX shared library libopengl_widget.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opengl_widget.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/opengl_widget.dir/build: libopengl_widget.so
.PHONY : CMakeFiles/opengl_widget.dir/build

CMakeFiles/opengl_widget.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/opengl_widget.dir/cmake_clean.cmake
.PHONY : CMakeFiles/opengl_widget.dir/clean

CMakeFiles/opengl_widget.dir/depend: include/moc_opengl_widget.cpp
CMakeFiles/opengl_widget.dir/depend: src/moc_opengl_widget.cpp
	cd /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build /home/nikl/Git/Galaxy-Renderer/QtOpenGlTest/build/CMakeFiles/opengl_widget.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/opengl_widget.dir/depend

