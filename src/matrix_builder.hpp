#pragma once
#include <vector>
#include <tuple>

using MatrixEntry = std::tuple<int, int, double>;

std::vector<MatrixEntry> buildSparseMatrix(int rank, int size, int N);