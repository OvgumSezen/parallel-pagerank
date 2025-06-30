#pragma once

#include <vector>

#include "COOMatrix.hpp"


class PageRankSolverMPI {
    public:
        static std::vector<double> solve(const COOMatrix& M, int max_iter = 1000, double tol = 1e-6);
};
