project(gtest)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/exe)

add_executable(gtest main.cpp
        ../lib/alg.cpp                                      ../lib/alg.hpp
        ../lib/app_ex.cpp                                   ../lib/app_ex.hpp
        ../lib/DateTime.cpp                                 ../lib/DateTime.h
                                                            ../lib/def.h
        ../lib/model_def.hpp
        ../lib/napisy.cpp                                   ../lib/napisy.h
        ../lib/Operators.cpp                                ../lib/Operators.h
        ../lib/ParamsForFilter.cpp                          ../lib/ParamsForFilter.h
        ../lib/PolishExpression.cpp                         ../lib/PolishExpression.h
        ../lib/PolishNotation.cpp                           ../lib/PolishNotation.h


#        ../lib/alg.cpp
#        ../lib/alg.h
#        ../lib/alg.h
#        ../lib/DateTime-2.cpp
#        ../lib/DateTime-2.h
#        ../lib/strings.cpp
#        ../lib/strings.h

        DateTimeTest.cpp
        DateTimeTest.h
        )
 
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(..)

set(Boost_DEBUG OFF)
find_package(Boost)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()


target_link_libraries(gtest
        ${GTEST_LIBRARIES}
        pthread
        boost_date_time
        )
