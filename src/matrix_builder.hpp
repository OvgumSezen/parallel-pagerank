#pragma once
#include <vector>
#include <tuple>

using MatrixEntry = std::tuple<int, int, double>;

std::vector<MatrixEntry> build_sparse_matrix(int rank, int size, int N);