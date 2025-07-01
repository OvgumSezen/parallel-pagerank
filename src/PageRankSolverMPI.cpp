#include <cmath>
#include <mpi.h>
#include <vector>

#include "include/PageRankSolverMPI.hpp"

std::vector<double> PageRankSolverMPI::solve(const COOMatrix& M, const int max_iter, const double tol) {
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    const int N = M.rows;

    std::vector<int> counts(world_size), displs(world_size);
    const int base = N / world_size;
    const int rem = N % world_size;
    for (int i = 0; i < world_size; ++i) {
        counts[i] = base + (i < rem ? 1 : 0);
        displs[i] = (i == 0) ? 0 : displs[i - 1] + counts[i - 1];
    }

    const int local_rows = counts[world_rank];
    const int start_row = displs[world_rank];

    std::vector<int> local_i, local_j;
    std::vector<double> local_val;
    for (size_t k = 0; k < M.values.size(); ++k) {
        const int global_i = M.row_indices[k];
        if (global_i >= start_row && global_i < start_row + local_rows) {
            local_i.push_back(global_i - start_row);
            local_j.push_back(M.col_indices[k]);
            local_val.push_back(M.values[k]);
        }
    }

    std::vector<double> u(N, 1.0 / N);
    std::vector<double> local_result(local_rows, 0.0);
    std::vector<double> gathered_result(N, 0.0);

    for (int iter = 0; iter < max_iter; ++iter) {
        std::fill(local_result.begin(), local_result.end(), 0.0);

        for (size_t k = 0; k < local_val.size(); ++k) {
            local_result[local_i[k]] += local_val[k] * u[local_j[k]];
        }

        MPI_Allgatherv(local_result.data(), local_rows, MPI_DOUBLE,
                       gathered_result.data(), counts.data(), displs.data(), MPI_DOUBLE,
                       MPI_COMM_WORLD);

        double local_error = 0.0;
        for (int i = 0; i < local_rows; ++i) {
            const double diff = gathered_result[start_row + i] - u[start_row + i];
            local_error += std::abs(diff);
        }

        double global_error = 0.0;
        MPI_Allreduce(&local_error, &global_error, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        if (global_error < tol) break;

        u = gathered_result;
    }

    return u;
}
