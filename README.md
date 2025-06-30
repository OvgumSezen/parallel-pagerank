# Parallel PageRank with MPI and C++

This project implements the PageRank algorithm in C++ using MPI for parallelization. It is built with CMake for portability and ease of use.

## 🔧 Requirements
- C++ compiler supporting C++11 or later
- MPI library (e.g., OpenMPI, MPICH)
- CMake 3.10 or higher

## 🚧 Build Instructions

1. **Create a build directory and enter it:**
   ```bash
   mkdir build
   cd build

2. **Generate the build system:**
    ```bash
   cmake..

3. **Build the project:**
   ```bash
   cmake --build .

## 🚀 Running the Experiment

1. **Serial Execution** \
    Run the application with a single process to get the baseline performance 
    measurements of the serial implementation of the algorithm.
    
    ```bash
   mpirun -np 1 ./parallel-pagerank

2. **Set Baseline in Code** \
    After running the algorithm on a single process record the execution time
    either from the terminal output or the measurements.csv file generated in
    the /build directory. The record should be set inside the main.cpp file by
    editing the line
    ```cpp
   const double t1_baseline = 0.0;

3. **Recompile** \
    After setting the value in the main.cpp file you need to recompıle by
    re-running the below command inside the /build directory:
    ```bash
   cmake --build .

4. **Parallel Execution** \
    Lastly, run the algorithm by increasing the number of processes from 2 to
    as high as you want or your machine allows.
    ```bash
   mpirun -np <N> ./parallel-pagerank
   
The results of the experiment will be recorded in the file /build/measurements.csv

   
