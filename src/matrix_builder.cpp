#include "matrix_builder.hpp"

/**
 * Builds the sparse adjacency matrix.
 * Only the non-zero values are stored for memory optimization.
 * Matrix is held in COO (Coordinate List) format, a set of triplets denoting the row_idx, col_idx and the value.
 * @param rank := rank of the process
 * @param size := number of processes
 * @param N := total number of pages
 * @return the COO representation of the page connection matrix
 */
std::vector<MatrixEntry> build_sparse_matrix(const int rank, const int size, const int N) {
    const int rows_per_rank = N / size;
    const int remainder = N % size;

    const int start_row = rank * rows_per_rank + std::min(rank, remainder);
    const int num_rows = rows_per_rank + (rank < remainder ? 1 : 0);
    const int end_row = start_row + num_rows;

    std::vector<MatrixEntry> local_entries;
    for (int i = start_row; i < end_row; ++i) {
        if (i + 1 < N) {
            local_entries.emplace_back(i, i+1, 1.0);
        }
        if (i >= 2) {
            local_entries.emplace_back(i, 2, 1.0);
        }
    }

    return local_entries;
}