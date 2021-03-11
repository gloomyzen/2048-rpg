return()
include(${CMAKE_SOURCE_DIR}/cmake/AddGoogleTest.cmake)

set(TEST_HEADER)
set(TEST_SOURCE)
file(GLOB_RECURSE TEST_HEADER ${CMAKE_SOURCE_DIR}/src/*.h ${CMAKE_SOURCE_DIR}/include/*.hpp)
file(GLOB_RECURSE TEST_SOURCE ${CMAKE_SOURCE_DIR}/src/*.cpp)

function(INIT_TEST ARG_TARGET)
    add_executable(${ARG_TARGET} ${ARGN})
    target_compile_features(${ARG_TARGET} PRIVATE cxx_std_17)
    target_compile_options(${ARG_TARGET} PRIVATE -Wall)
    add_gtest(${ARG_TARGET})
endfunction()

function(ADD_DEPS_TO_TEST ARG_TARGET)
    target_link_libraries(
            ${ARG_TARGET} PUBLIC ${ARGN})
endfunction()

################### General tests ###################
#init_test(TestJsonDeps ./TestJsonDeps.cpp)
#add_deps_to_test(TestJsonDeps ${PROJECT_NAME})

#################### Core Module ####################
#init_test(TestVector2D ./TestVector2D.cpp ../src/Core/DataTypes/Vector2D.cpp ../src/Core/DataTypes/Vector2D.h)
#add_deps_to_test(TestVector2D ${PROJECT_NAME})

