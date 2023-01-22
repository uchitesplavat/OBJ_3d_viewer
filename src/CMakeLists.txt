cmake_minimum_required(VERSION 3.5)

project(viewer_test VERSION 0.1 LANGUAGES CXX C)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-lGL -lGLU -lglut -lm")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS OpenGL)

set(PROJECT_SOURCES
        qt/main.cpp
        qt/mainwindow.cpp
        qt/mainwindow.h
        qt/mainwindow.ui
        widget.cpp
        widget.h
        parser.c
        parser.h
        helpers/affin_transform.c
        view_config_save.c
        helpers/helpers.c
        helpers/helpers.h
        view_config_save.c
        gif/giflib/dgif_lib.c
        gif/giflib/egif_lib.c
        gif/giflib/gif_err.c
        gif/giflib/gif_hash.c
        gif/giflib/gifalloc.c
        gif/giflib/quantize.c
        gif/giflib/gif_font.c
        gif/giflib/gif_hash.h
        gif/giflib/gif_lib.h
        gif/giflib/gif_lib_private.h
        gif/qgifimage.cpp
        gif/qgifglobal.h
        gif/qgifimage.h
        gif/qgifimage_p.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(viewer_test
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET viewer_test APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(viewer_test SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(viewer_test
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(viewer_test PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(viewer_test PUBLIC Qt${QT_VERSION_MAJOR}::OpenGL)

set_target_properties(viewer_test PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(viewer_test)
endif()
