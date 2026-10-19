cmake_minimum_required(VERSION 3.14)
project(SQA_FeeCalculator_Practice CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Compilar con flags de cobertura (GCC)" OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(runTests
  tests/test_fee_calculator.cpp
  src/FeeCalculator.cpp
)
target_include_directories(runTests PRIVATE src)
target_link_libraries(runTests gtest)

if(ENABLE_COVERAGE)
  target_compile_options(runTests PRIVATE -O0 -g -fprofile-arcs -ftest-coverage)
  target_link_options(runTests PRIVATE -fprofile-arcs -ftest-coverage)
endif()

include(GoogleTest)
gtest_discover_tests(runTests)
