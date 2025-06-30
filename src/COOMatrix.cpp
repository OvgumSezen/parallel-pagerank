#include "include/COOMatrix.hpp"

COOMatrix::COOMatrix(const int r, const int c) : rows(r), cols(c) {}

void COOMatrix::add_entry(const int i, const int j, const double val) {
    row_indices.push_back(i);
    col_indices.push_back(j);
    values.push_back(val);
}

void COOMatrix::matvec(const std::vector<double> &x, std::vector<double> &result) const {
    result.assign(rows, 0.0);
    for (size_t k = 0; k < values.size(); ++k) {
        result[row_indices[k]] += values[k] * x[col_indices[k]];
    }
}

