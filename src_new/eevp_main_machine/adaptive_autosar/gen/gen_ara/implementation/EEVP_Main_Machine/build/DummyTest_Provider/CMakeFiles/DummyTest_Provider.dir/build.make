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
CMAKE_SOURCE_DIR = /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build

# Include any dependencies generated for this target.
include DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/compiler_depend.make

# Include the progress variables for this target.
include DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/progress.make

# Include the compile flags for this target's objects.
include DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/flags.make

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/flags.make
DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o: ../DummyTest_Provider/src/main.cpp
DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o -MF CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o.d -o CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o -c /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider/src/main.cpp

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DummyTest_Provider.dir/src/main.cpp.i"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider/src/main.cpp > CMakeFiles/DummyTest_Provider.dir/src/main.cpp.i

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DummyTest_Provider.dir/src/main.cpp.s"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider/src/main.cpp -o CMakeFiles/DummyTest_Provider.dir/src/main.cpp.s

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/flags.make
DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o: ../DummyTest_Provider/src/provider.cpp
DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o -MF CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o.d -o CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o -c /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider/src/provider.cpp

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.i"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider/src/provider.cpp > CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.i

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.s"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider/src/provider.cpp -o CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.s

# Object files for target DummyTest_Provider
DummyTest_Provider_OBJECTS = \
"CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o" \
"CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o"

# External object files for target DummyTest_Provider
DummyTest_Provider_EXTERNAL_OBJECTS =

DummyTest_Provider/DummyTest_Provider: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/main.cpp.o
DummyTest_Provider/DummyTest_Provider: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/src/provider.cpp.o
DummyTest_Provider/DummyTest_Provider: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/build.make
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_core.so.1.0.0
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_com.so.1.0.0
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_per.so.1.0.0
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_iam.so.1.0.0
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_exec.so.1.0.0
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_base.so.1.0.0
DummyTest_Provider/DummyTest_Provider: /home/popcornsar/work/para-sdk/lib/libpara_log.so.1.0.0
DummyTest_Provider/DummyTest_Provider: DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable DummyTest_Provider"
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DummyTest_Provider.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/build: DummyTest_Provider/DummyTest_Provider
.PHONY : DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/build

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/clean:
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider && $(CMAKE_COMMAND) -P CMakeFiles/DummyTest_Provider.dir/cmake_clean.cmake
.PHONY : DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/clean

DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/depend:
	cd /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/DummyTest_Provider /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider /home/popcornsar/src/eevp_main_machine/adaptive_autosar/gen/gen_ara/implementation/EEVP_Main_Machine/build/DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : DummyTest_Provider/CMakeFiles/DummyTest_Provider.dir/depend
