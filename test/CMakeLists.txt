project(test)


add_executable(test_run main.cpp
        )

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(Boost_DEBUG OFF)
find_package(Boost)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()


target_link_libraries(test_run
        ${GTEST_LIBRARIES}
        pthread
        )
