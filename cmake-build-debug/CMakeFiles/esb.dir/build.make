# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.9

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "E:\Program Files\CLion 2017.3.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "E:\Program Files\CLion 2017.3.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\fernando\Source\Repos\esb

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\fernando\Source\Repos\esb\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\esb.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\esb.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\esb.dir\flags.make

CMakeFiles\esb.dir\main.cpp.obj: CMakeFiles\esb.dir\flags.make
CMakeFiles\esb.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\fernando\Source\Repos\esb\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/esb.dir/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1412~1.258\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\esb.dir\main.cpp.obj /FdCMakeFiles\esb.dir\ /FS -c C:\Users\fernando\Source\Repos\esb\main.cpp
<<

CMakeFiles\esb.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/esb.dir/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1412~1.258\bin\Hostx86\x86\cl.exe > CMakeFiles\esb.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\fernando\Source\Repos\esb\main.cpp
<<

CMakeFiles\esb.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/esb.dir/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1412~1.258\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\esb.dir\main.cpp.s /c C:\Users\fernando\Source\Repos\esb\main.cpp
<<

CMakeFiles\esb.dir\main.cpp.obj.requires:

.PHONY : CMakeFiles\esb.dir\main.cpp.obj.requires

CMakeFiles\esb.dir\main.cpp.obj.provides: CMakeFiles\esb.dir\main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\esb.dir\build.make /nologo -$(MAKEFLAGS) CMakeFiles\esb.dir\main.cpp.obj.provides.build
.PHONY : CMakeFiles\esb.dir\main.cpp.obj.provides

CMakeFiles\esb.dir\main.cpp.obj.provides.build: CMakeFiles\esb.dir\main.cpp.obj


# Object files for target esb
esb_OBJECTS = \
"CMakeFiles\esb.dir\main.cpp.obj"

# External object files for target esb
esb_EXTERNAL_OBJECTS =

esb.exe: CMakeFiles\esb.dir\main.cpp.obj
esb.exe: CMakeFiles\esb.dir\build.make
esb.exe: CMakeFiles\esb.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\fernando\Source\Repos\esb\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable esb.exe"
	"E:\Program Files\CLion 2017.3.2\bin\cmake\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\esb.dir --manifests  -- C:\PROGRA~2\MIB055~1\2017\COMMUN~1\VC\Tools\MSVC\1412~1.258\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\esb.dir\objects1.rsp @<<
 /out:esb.exe /implib:esb.lib /pdb:C:\Users\fernando\Source\Repos\esb\cmake-build-debug\esb.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  -LIBPATH:C:\Users\fernando\Downloads\boost_1_62_0\stage\lib kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\esb.dir\build: esb.exe

.PHONY : CMakeFiles\esb.dir\build

CMakeFiles\esb.dir\requires: CMakeFiles\esb.dir\main.cpp.obj.requires

.PHONY : CMakeFiles\esb.dir\requires

CMakeFiles\esb.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\esb.dir\cmake_clean.cmake
.PHONY : CMakeFiles\esb.dir\clean

CMakeFiles\esb.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\fernando\Source\Repos\esb C:\Users\fernando\Source\Repos\esb C:\Users\fernando\Source\Repos\esb\cmake-build-debug C:\Users\fernando\Source\Repos\esb\cmake-build-debug C:\Users\fernando\Source\Repos\esb\cmake-build-debug\CMakeFiles\esb.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\esb.dir\depend

