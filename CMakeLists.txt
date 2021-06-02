cmake_minimum_required(VERSION 3.10)

# set the project name
project(Fractals VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

configure_file(src/FractalsConfig.h.in FractalsConfig.h)

# adding boost dirs
FIND_PACKAGE( Boost 1.71 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

include_directories("${PROJECT_BINARY_DIR}")

# link libs
find_library(FREEGLUT_LIB glut)
find_library(GL_LIB GL)
find_library(GLU_LIB GLU)
find_library(THREADS_LIB pthread)
link_libraries("${FREEGLUT_LIB}" "${GL_LIB}" "${GLU_LIB}" "${Boost_LIBRARIES}" "${THREADS_LIB}")

# add the executable
add_executable(Fractals src/main.cpp src/fractal.h src/constants.h src/fractal.cpp src/generators.h src/generators.cpp src/colorPalette.cpp src/colorPalette.h src/palettes.h src/tmp.h)
set_target_properties(Fractals PROPERTIES COMPILE_FLAGS "-O2")
add_executable(FractalsDebug src/main.cpp src/fractal.h src/constants.h src/fractal.cpp src/generators.h src/generators.cpp src/colorPalette.cpp src/colorPalette.h src/palettes.h src/tmp.h)
set_target_properties(FractalsDebug PROPERTIES COMPILE_FLAGS "-O0 -ggdb")



