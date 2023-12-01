cmake_minimum_required(VERSION 3.14)

project("01-Trebuchet")

add_executable(${PROJECT_NAME} main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Copy input data file to outdir
file(COPY "input.txt" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

