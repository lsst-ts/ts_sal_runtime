# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
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
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dmills/sal/test/lsst-master/tma_management

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmills/sal/test/lsst-master/tma_management/build

# Include any dependencies generated for this target.
include CMakeFiles/test-time.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test-time.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test-time.dir/flags.make

CMakeFiles/test-time.dir/test/test-time.cpp.o: CMakeFiles/test-time.dir/flags.make
CMakeFiles/test-time.dir/test/test-time.cpp.o: ../test/test-time.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/dmills/sal/test/lsst-master/tma_management/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/test-time.dir/test/test-time.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/test-time.dir/test/test-time.cpp.o -c /home/dmills/sal/test/lsst-master/tma_management/test/test-time.cpp

CMakeFiles/test-time.dir/test/test-time.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test-time.dir/test/test-time.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/dmills/sal/test/lsst-master/tma_management/test/test-time.cpp > CMakeFiles/test-time.dir/test/test-time.cpp.i

CMakeFiles/test-time.dir/test/test-time.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test-time.dir/test/test-time.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/dmills/sal/test/lsst-master/tma_management/test/test-time.cpp -o CMakeFiles/test-time.dir/test/test-time.cpp.s

CMakeFiles/test-time.dir/test/test-time.cpp.o.requires:
.PHONY : CMakeFiles/test-time.dir/test/test-time.cpp.o.requires

CMakeFiles/test-time.dir/test/test-time.cpp.o.provides: CMakeFiles/test-time.dir/test/test-time.cpp.o.requires
	$(MAKE) -f CMakeFiles/test-time.dir/build.make CMakeFiles/test-time.dir/test/test-time.cpp.o.provides.build
.PHONY : CMakeFiles/test-time.dir/test/test-time.cpp.o.provides

CMakeFiles/test-time.dir/test/test-time.cpp.o.provides.build: CMakeFiles/test-time.dir/test/test-time.cpp.o

# Object files for target test-time
test__time_OBJECTS = \
"CMakeFiles/test-time.dir/test/test-time.cpp.o"

# External object files for target test-time
test__time_EXTERNAL_OBJECTS =

test-time: CMakeFiles/test-time.dir/test/test-time.cpp.o
test-time: CMakeFiles/test-time.dir/build.make
test-time: /usr/lib64/libboost_thread-mt.so
test-time: /usr/lib64/libboost_system-mt.so
test-time: /usr/lib64/libboost_timer-mt.so
test-time: /usr/lib64/libboost_date_time-mt.so
test-time: /usr/lib64/libboost_program_options-mt.so
test-time: CMakeFiles/test-time.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable test-time"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test-time.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test-time.dir/build: test-time
.PHONY : CMakeFiles/test-time.dir/build

CMakeFiles/test-time.dir/requires: CMakeFiles/test-time.dir/test/test-time.cpp.o.requires
.PHONY : CMakeFiles/test-time.dir/requires

CMakeFiles/test-time.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test-time.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test-time.dir/clean

CMakeFiles/test-time.dir/depend:
	cd /home/dmills/sal/test/lsst-master/tma_management/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmills/sal/test/lsst-master/tma_management /home/dmills/sal/test/lsst-master/tma_management /home/dmills/sal/test/lsst-master/tma_management/build /home/dmills/sal/test/lsst-master/tma_management/build /home/dmills/sal/test/lsst-master/tma_management/build/CMakeFiles/test-time.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test-time.dir/depend

