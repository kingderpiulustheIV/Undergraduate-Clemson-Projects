# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build"

# Include any dependencies generated for this target.
include CMakeFiles/Lab_7.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Lab_7.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Lab_7.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Lab_7.dir/flags.make

CMakeFiles/Lab_7.dir/ppmDriver.c.obj: CMakeFiles/Lab_7.dir/flags.make
CMakeFiles/Lab_7.dir/ppmDriver.c.obj: CMakeFiles/Lab_7.dir/includes_C.rsp
CMakeFiles/Lab_7.dir/ppmDriver.c.obj: C:/Users/sfarr/OneDrive/Desktop/cpsc\ 2310/Lab\ 7/ppmDriver.c
CMakeFiles/Lab_7.dir/ppmDriver.c.obj: CMakeFiles/Lab_7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Lab_7.dir/ppmDriver.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Lab_7.dir/ppmDriver.c.obj -MF CMakeFiles\Lab_7.dir\ppmDriver.c.obj.d -o CMakeFiles\Lab_7.dir\ppmDriver.c.obj -c "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\ppmDriver.c"

CMakeFiles/Lab_7.dir/ppmDriver.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Lab_7.dir/ppmDriver.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\ppmDriver.c" > CMakeFiles\Lab_7.dir\ppmDriver.c.i

CMakeFiles/Lab_7.dir/ppmDriver.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Lab_7.dir/ppmDriver.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\ppmDriver.c" -o CMakeFiles\Lab_7.dir\ppmDriver.c.s

CMakeFiles/Lab_7.dir/ppmUtil.c.obj: CMakeFiles/Lab_7.dir/flags.make
CMakeFiles/Lab_7.dir/ppmUtil.c.obj: CMakeFiles/Lab_7.dir/includes_C.rsp
CMakeFiles/Lab_7.dir/ppmUtil.c.obj: C:/Users/sfarr/OneDrive/Desktop/cpsc\ 2310/Lab\ 7/ppmUtil.c
CMakeFiles/Lab_7.dir/ppmUtil.c.obj: CMakeFiles/Lab_7.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Lab_7.dir/ppmUtil.c.obj"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/Lab_7.dir/ppmUtil.c.obj -MF CMakeFiles\Lab_7.dir\ppmUtil.c.obj.d -o CMakeFiles\Lab_7.dir\ppmUtil.c.obj -c "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\ppmUtil.c"

CMakeFiles/Lab_7.dir/ppmUtil.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/Lab_7.dir/ppmUtil.c.i"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\ppmUtil.c" > CMakeFiles\Lab_7.dir\ppmUtil.c.i

CMakeFiles/Lab_7.dir/ppmUtil.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/Lab_7.dir/ppmUtil.c.s"
	C:\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\ppmUtil.c" -o CMakeFiles\Lab_7.dir\ppmUtil.c.s

# Object files for target Lab_7
Lab_7_OBJECTS = \
"CMakeFiles/Lab_7.dir/ppmDriver.c.obj" \
"CMakeFiles/Lab_7.dir/ppmUtil.c.obj"

# External object files for target Lab_7
Lab_7_EXTERNAL_OBJECTS =

Lab_7.exe: CMakeFiles/Lab_7.dir/ppmDriver.c.obj
Lab_7.exe: CMakeFiles/Lab_7.dir/ppmUtil.c.obj
Lab_7.exe: CMakeFiles/Lab_7.dir/build.make
Lab_7.exe: CMakeFiles/Lab_7.dir/linkLibs.rsp
Lab_7.exe: CMakeFiles/Lab_7.dir/objects1.rsp
Lab_7.exe: CMakeFiles/Lab_7.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Lab_7.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\Lab_7.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Lab_7.dir/build: Lab_7.exe
.PHONY : CMakeFiles/Lab_7.dir/build

CMakeFiles/Lab_7.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Lab_7.dir\cmake_clean.cmake
.PHONY : CMakeFiles/Lab_7.dir/clean

CMakeFiles/Lab_7.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7" "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7" "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build" "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build" "C:\Users\sfarr\OneDrive\Desktop\cpsc 2310\Lab 7\build\CMakeFiles\Lab_7.dir\DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/Lab_7.dir/depend

