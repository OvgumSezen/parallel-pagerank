cmake_minimum_required(VERSION 3.28.3)
project(parallel_pagerank)

find_package(MPI REQUIRED)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/COOMatrix.cpp
        src/Graph.cpp
        src/PageRankSolver.cpp
        src/PageRankSolverMPI.cpp
        src/Measurement.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${PROJECT_NAME} PRIVATE MPI::MPI_CXX)