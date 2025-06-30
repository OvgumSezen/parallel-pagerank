#include <vector>
#include <cmath>

#include "include/PageRankSolver.hpp"

std::vector<double> PageRankSolver::solve(const COOMatrix& M, const int max_iter, const double tol) {
    const int N = M.rows;
    std::vector<double> u(N, 1.0 / N), u_next(N, 0.0);

    for (int iter = 0; iter < max_iter; ++iter) {
        M.matvec(u, u_next);

        double err = 0.0;
        for (int i = 0; i < N; ++i)
            err += std::abs(u_next[i] - u[i]);

        if (err < tol) break;
        u = u_next;
    }

    return u;
}
