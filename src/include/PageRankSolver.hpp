#pragma once

#include "COOMatrix.hpp"

class PageRankSolver {
    public:
        static std::vector<double> solve(const COOMatrix& M, int max_iter = 1000, double tol = 1e-6);
};
