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

set(TS_FILES translations/zh_CN.ts)

set(PROJECT_SOURCES
        src/main.cpp
        src/mainwindow.cpp
        src/mainwindow.h
        src/mainwindow.ui
        src/core.cpp
        src/core.h
        src/scopeguard.h
        src/aria2ctrl.h
        src/aria2ctrl.cpp
        src/aria2client.cpp
        src/aia2client.h
        src/eventlogwidget.cpp
        src/eventlogwidget.h
        src/eventlogwidget.ui
        )

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/hunt.qrc")

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(hunt
            ${PROJECT_SOURCES}
            ${TS_FILES}
            ${APP_ICON_RESOURCE_WINDOWS}
            )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    if (ANDROID)
        add_library(hunt SHARED
                ${PROJECT_SOURCES}
                ${TS_FILES}
                ${APP_ICON_RESOURCE_WINDOWS}
                )
    else ()
        add_executable(hunt
                ${PROJECT_SOURCES}
                ${TS_FILES}
                ${APP_ICON_RESOURCE_WINDOWS}
                )
    endif ()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

set(Qt_COMPONENTS
        Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::WebSockets)

target_link_libraries(hunt PRIVATE ${Qt_COMPONENTS})
redefine_file_macro(hunt __HUNT_FILE__)

add_subdirectory(tests)
