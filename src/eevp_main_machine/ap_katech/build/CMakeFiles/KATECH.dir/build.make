# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/popcornsar/src/eevp_main_machine/ap_katech

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/popcornsar/src/eevp_main_machine/ap_katech/build

# Include any dependencies generated for this target.
include CMakeFiles/KATECH.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/KATECH.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/KATECH.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/KATECH.dir/flags.make

CMakeFiles/KATECH.dir/src/main.cpp.o: CMakeFiles/KATECH.dir/flags.make
CMakeFiles/KATECH.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/KATECH.dir/src/main.cpp.o: CMakeFiles/KATECH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/popcornsar/src/eevp_main_machine/ap_katech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/KATECH.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/KATECH.dir/src/main.cpp.o -MF CMakeFiles/KATECH.dir/src/main.cpp.o.d -o CMakeFiles/KATECH.dir/src/main.cpp.o -c /home/popcornsar/src/eevp_main_machine/ap_katech/src/main.cpp

CMakeFiles/KATECH.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KATECH.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/popcornsar/src/eevp_main_machine/ap_katech/src/main.cpp > CMakeFiles/KATECH.dir/src/main.cpp.i

CMakeFiles/KATECH.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KATECH.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/popcornsar/src/eevp_main_machine/ap_katech/src/main.cpp -o CMakeFiles/KATECH.dir/src/main.cpp.s

CMakeFiles/KATECH.dir/src/katech.cpp.o: CMakeFiles/KATECH.dir/flags.make
CMakeFiles/KATECH.dir/src/katech.cpp.o: ../src/katech.cpp
CMakeFiles/KATECH.dir/src/katech.cpp.o: CMakeFiles/KATECH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/popcornsar/src/eevp_main_machine/ap_katech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/KATECH.dir/src/katech.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/KATECH.dir/src/katech.cpp.o -MF CMakeFiles/KATECH.dir/src/katech.cpp.o.d -o CMakeFiles/KATECH.dir/src/katech.cpp.o -c /home/popcornsar/src/eevp_main_machine/ap_katech/src/katech.cpp

CMakeFiles/KATECH.dir/src/katech.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KATECH.dir/src/katech.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/popcornsar/src/eevp_main_machine/ap_katech/src/katech.cpp > CMakeFiles/KATECH.dir/src/katech.cpp.i

CMakeFiles/KATECH.dir/src/katech.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KATECH.dir/src/katech.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/popcornsar/src/eevp_main_machine/ap_katech/src/katech.cpp -o CMakeFiles/KATECH.dir/src/katech.cpp.s

CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o: CMakeFiles/KATECH.dir/flags.make
CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o: ../src/RoaProxyImpl.cpp
CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o: CMakeFiles/KATECH.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/popcornsar/src/eevp_main_machine/ap_katech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o -MF CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o.d -o CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o -c /home/popcornsar/src/eevp_main_machine/ap_katech/src/RoaProxyImpl.cpp

CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/popcornsar/src/eevp_main_machine/ap_katech/src/RoaProxyImpl.cpp > CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.i

CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/popcornsar/src/eevp_main_machine/ap_katech/src/RoaProxyImpl.cpp -o CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.s

# Object files for target KATECH
KATECH_OBJECTS = \
"CMakeFiles/KATECH.dir/src/main.cpp.o" \
"CMakeFiles/KATECH.dir/src/katech.cpp.o" \
"CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o"

# External object files for target KATECH
KATECH_EXTERNAL_OBJECTS =

KATECH: CMakeFiles/KATECH.dir/src/main.cpp.o
KATECH: CMakeFiles/KATECH.dir/src/katech.cpp.o
KATECH: CMakeFiles/KATECH.dir/src/RoaProxyImpl.cpp.o
KATECH: CMakeFiles/KATECH.dir/build.make
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_core.so.1.0.0
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_com.so.1.0.0
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_per.so.1.0.0
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_iam.so.1.0.0
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_exec.so.1.0.0
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_base.so.1.0.0
KATECH: /home/popcornsar/work/para-sdk/lib/libpara_log.so.1.0.0
KATECH: CMakeFiles/KATECH.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/popcornsar/src/eevp_main_machine/ap_katech/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable KATECH"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/KATECH.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/KATECH.dir/build: KATECH
.PHONY : CMakeFiles/KATECH.dir/build

CMakeFiles/KATECH.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/KATECH.dir/cmake_clean.cmake
.PHONY : CMakeFiles/KATECH.dir/clean

CMakeFiles/KATECH.dir/depend:
	cd /home/popcornsar/src/eevp_main_machine/ap_katech/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/popcornsar/src/eevp_main_machine/ap_katech /home/popcornsar/src/eevp_main_machine/ap_katech /home/popcornsar/src/eevp_main_machine/ap_katech/build /home/popcornsar/src/eevp_main_machine/ap_katech/build /home/popcornsar/src/eevp_main_machine/ap_katech/build/CMakeFiles/KATECH.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/KATECH.dir/depend

