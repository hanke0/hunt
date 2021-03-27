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
