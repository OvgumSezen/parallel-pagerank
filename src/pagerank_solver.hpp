#pragma once
#include <tuple>
#include <vector>


using MatrixEntry = std::tuple<int, int, double>;

std::vector<double> run_power_method(
    const std::vector<MatrixEntry>& local_matrix,
    int N,
    int rank,
    int size,
    double p = 0.85,
    int max_iter = 1000,
    double tol = 1e-10);