#include "pagerank_solver.hpp"

std::vector<double> run_power_method(
    const std::vector<MatrixEntry>& local_matrix,
    int N,
    int rank,
    int size,
    double p,
    int max_iter,
    double tol) {
    // TODO: Implement the calculation logic.
    std::vector<double> u(N, 1.0 / N);
    return u;
}