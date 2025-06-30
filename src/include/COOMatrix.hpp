#pragma once

#include <vector>

class COOMatrix {
    public:
        int rows, cols;
        std::vector<int> row_indices, col_indices;
        std::vector<double> values;

        COOMatrix(int r, int c);
        void add_entry(int i , int j, double val);
        void matvec(const std::vector<double>& x, std::vector<double>& result) const;
};
