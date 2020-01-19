project(test)


add_executable(test_run main.cpp
        ../lib/alg.cpp
        ../lib/alg.h
        ../lib/DateTime.cpp
        ../lib/DateTime.h
        ../lib/DateTime-2.cpp
        ../lib/DateTime2.h
        ../lib/napisy.cpp
        ../lib/napisy.h
        ../lib/Operators.cpp
        ../lib/Operators.h
        ../lib/PolishExpression.cpp
        ../lib/PolishExpression.h
        ../lib/PolishNotation.cpp
        ../lib/PolishNotation.h
        ../lib/strings.cpp
        ../lib/strings.h
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
