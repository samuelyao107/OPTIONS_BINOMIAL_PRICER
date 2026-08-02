cmake_minimum_required(VERSION 3.15)
project(BinomialPricer VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options d'optimisation pour la performance
if(MSVC)
    add_compile_options(/W4 /O2)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -O3)
endif()

include_directories(include)

add_library(binomial_engine
    src/Payoff.cpp
    src/Option.cpp
    src/BinomialTreeEngine.cpp
)

add_executable(binomial_example examples/main.cpp)
target_link_libraries(binomial_example PRIVATE binomial_engine)

add_executable(binomial_tests tests/test_binomial.cpp)
target_link_libraries(binomial_tests PRIVATE binomial_engine)