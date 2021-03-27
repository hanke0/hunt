cmake_minimum_required(VERSION 3.5)

project(hunt LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/relative.cmake)

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

find_package(QT NAMES Qt5 COMPONENTS Core Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Widgets LinguistTools WebSockets REQUIRED)

include_directories(src)

set(TS_FILES
        translations/zh_CN.ts
        )

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/core.cpp
        src/core.h
        src/scopeguard.h
        src/aria2ctrl.h
        src/aria2ctrl.cpp
        src/aria2client.cpp
        src/aria2client.h
        src/eventlogwidget.cpp
        src/eventlogwidget.h
        src/sidebar.cpp
        src/sidebar.h
        src/statusbar.cpp
        src/statusbar.h
        src/menubar.cpp
        src/menubar.h
        src/centralwidget.cpp
        src/centralwidget.h
        )

qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TS_FILES})
add_custom_target(translations DEPENDS ${QM_FILES})
# The qm files are generated in the build tree, but the qrc file is inside the
# source directory and the path to resources are relative to the location of
# the qrc file itself. We use configure_file() to copy the qrc file in the build
# directory such that it can find the qm translations files. The qrc file is
# copied if it doesn't exist in the destination or if it is modified.
configure_file(translations/translations.qrc ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

set(HUNT_RESOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/hunt.qrc"
        ${CMAKE_CURRENT_BINARY_DIR}/translations.qrc
        )

if (ANDROID)
    add_library(hunt SHARED
            ${PROJECT_SOURCES}
            ${TS_FILES}
            ${HUNT_RESOURCES}
            )
else ()
    add_executable(hunt
            ${PROJECT_SOURCES}
            ${TS_FILES}
            ${HUNT_RESOURCES}
            )
endif ()

set(Qt_COMPONENTS Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::WebSockets)

target_link_libraries(hunt PRIVATE ${Qt_COMPONENTS})
redefine_file_macro(hunt __HUNT_FILE__)

# target test
find_package(Qt${QT_VERSION_MAJOR}Test REQUIRED)
add_executable(hunt_test
        tests/hunt_test.cpp
        tests/hunt_test.h
        src/scopeguard.h
        src/aria2ctrl.cpp
        src/aria2ctrl.h
        )
target_link_libraries(hunt_test PRIVATE
        Qt${QT_VERSION_MAJOR}::Test ${Qt_COMPONENTS})
add_test(hunt_test hunt_test)
redefine_file_macro(hunt_test __HUNT_FILE__)
