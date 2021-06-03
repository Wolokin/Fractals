cmake_minimum_required(VERSION 3.5)

project(Fractals VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# compiler flags
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")

configure_file(src/FractalsConfig.h.in FractalsConfig.h)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/mydialog.h src/mydialog.cpp src/mydialog.ui
        src/myglwidget.h src/myglwidget.cpp src/myglwidget.ui
        src/fractal.h 
        src/constants.h 
        src/fractal.cpp 
        src/generators.h 
        src/generators.cpp 
        src/colorPalette.cpp 
        src/colorPalette.h 
        src/palettes.h 
        src/tmp.h
        src/oglwidget.h src/oglwidget.cpp
        src/combobox_fractals.h src/combobox_fractals.cpp
        src/combobox_palettes.h src/combobox_palettes.cpp
        src/fractals.cpp
)

# adding boost dirs
FIND_PACKAGE( Boost 1.71 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

include_directories("./src")

find_library(FREEGLUT_LIB glut)
find_library(GL_LIB GL)
find_library(GLU_LIB GLU)
find_library(THREADS_LIB pthread)
link_libraries("${FREEGLUT_LIB}" "${GL_LIB}" "${GLU_LIB}" "${Boost_LIBRARIES}" "${THREADS_LIB}")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Fractals
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(Fractals SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(Fractals
            ${PROJECT_SOURCES}
        )
    endif()
endif()



target_link_libraries(Fractals PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Fractals PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Fractals)
endif()
