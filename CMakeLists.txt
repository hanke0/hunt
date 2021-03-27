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

set(TS_FILES hunt_zh_CN.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        core.cpp
        core.h
        scopeguard.h
        aria2ctrl.h
        aria2ctrl.cpp
        aria2client.cpp
        aria2client.h
        eventlogwidget.cpp
        eventlogwidget.h
        eventlogwidget.ui
        ${TS_FILES}
        )

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hunt
            ${PROJECT_SOURCES}
            ${TS_FILES}
            )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    if (ANDROID)
        add_library(hunt SHARED
                ${PROJECT_SOURCES}
                ${TS_FILES}
                )
    else ()
        add_executable(hunt
                ${PROJECT_SOURCES}
                ${TS_FILES}
                )
    endif ()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

set(Qt_COMPONENTS
        Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::WebSockets)

target_link_libraries(hunt PRIVATE ${Qt_COMPONENTS})
redefine_file_macro(hunt __HUNT_FILE__)

# ------------------ test ------------------------- #
find_package(Qt${QT_VERSION_MAJOR}Test REQUIRED)
add_executable(hunt_test
        hunt_test.cpp hunt_test.h
        scopeguard.h
        aria2ctrl.cpp
        aria2ctrl.h
        )
target_link_libraries(hunt_test PRIVATE
        Qt${QT_VERSION_MAJOR}::Test ${Qt_COMPONENTS})
add_test(hunt_test hunt_test)
redefine_file_macro(hunt_test __HUNT_FILE__)
