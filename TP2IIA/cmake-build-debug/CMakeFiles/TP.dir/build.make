# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\king_\Desktop\TPIIA2-master

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/TP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/TP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/TP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TP.dir/flags.make

CMakeFiles/TP.dir/main.c.obj: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/main.c.obj: C:/Users/king_/Desktop/TPIIA2-master/main.c
CMakeFiles/TP.dir/main.c.obj: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/TP.dir/main.c.obj"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TP.dir/main.c.obj -MF CMakeFiles\TP.dir\main.c.obj.d -o CMakeFiles\TP.dir\main.c.obj -c C:\Users\king_\Desktop\TPIIA2-master\main.c

CMakeFiles/TP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TP.dir/main.c.i"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\king_\Desktop\TPIIA2-master\main.c > CMakeFiles\TP.dir\main.c.i

CMakeFiles/TP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TP.dir/main.c.s"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\king_\Desktop\TPIIA2-master\main.c -o CMakeFiles\TP.dir\main.c.s

CMakeFiles/TP.dir/algoritmo.c.obj: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/algoritmo.c.obj: C:/Users/king_/Desktop/TPIIA2-master/algoritmo.c
CMakeFiles/TP.dir/algoritmo.c.obj: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/TP.dir/algoritmo.c.obj"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TP.dir/algoritmo.c.obj -MF CMakeFiles\TP.dir\algoritmo.c.obj.d -o CMakeFiles\TP.dir\algoritmo.c.obj -c C:\Users\king_\Desktop\TPIIA2-master\algoritmo.c

CMakeFiles/TP.dir/algoritmo.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TP.dir/algoritmo.c.i"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\king_\Desktop\TPIIA2-master\algoritmo.c > CMakeFiles\TP.dir\algoritmo.c.i

CMakeFiles/TP.dir/algoritmo.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TP.dir/algoritmo.c.s"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\king_\Desktop\TPIIA2-master\algoritmo.c -o CMakeFiles\TP.dir\algoritmo.c.s

CMakeFiles/TP.dir/utils.c.obj: CMakeFiles/TP.dir/flags.make
CMakeFiles/TP.dir/utils.c.obj: C:/Users/king_/Desktop/TPIIA2-master/utils.c
CMakeFiles/TP.dir/utils.c.obj: CMakeFiles/TP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/TP.dir/utils.c.obj"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/TP.dir/utils.c.obj -MF CMakeFiles\TP.dir\utils.c.obj.d -o CMakeFiles\TP.dir\utils.c.obj -c C:\Users\king_\Desktop\TPIIA2-master\utils.c

CMakeFiles/TP.dir/utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/TP.dir/utils.c.i"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\king_\Desktop\TPIIA2-master\utils.c > CMakeFiles\TP.dir\utils.c.i

CMakeFiles/TP.dir/utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/TP.dir/utils.c.s"
	"C:\PROGRA~1\JetBrains\CLion 2023.3.1\bin\mingw\bin\gcc.exe" $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\king_\Desktop\TPIIA2-master\utils.c -o CMakeFiles\TP.dir\utils.c.s

# Object files for target TP
TP_OBJECTS = \
"CMakeFiles/TP.dir/main.c.obj" \
"CMakeFiles/TP.dir/algoritmo.c.obj" \
"CMakeFiles/TP.dir/utils.c.obj"

# External object files for target TP
TP_EXTERNAL_OBJECTS =

TP.exe: CMakeFiles/TP.dir/main.c.obj
TP.exe: CMakeFiles/TP.dir/algoritmo.c.obj
TP.exe: CMakeFiles/TP.dir/utils.c.obj
TP.exe: CMakeFiles/TP.dir/build.make
TP.exe: CMakeFiles/TP.dir/linkLibs.rsp
TP.exe: CMakeFiles/TP.dir/objects1.rsp
TP.exe: CMakeFiles/TP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable TP.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\TP.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TP.dir/build: TP.exe
.PHONY : CMakeFiles/TP.dir/build

CMakeFiles/TP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\TP.dir\cmake_clean.cmake
.PHONY : CMakeFiles/TP.dir/clean

CMakeFiles/TP.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\king_\Desktop\TPIIA2-master C:\Users\king_\Desktop\TPIIA2-master C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug C:\Users\king_\Desktop\TPIIA2-master\cmake-build-debug\CMakeFiles\TP.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/TP.dir/depend
