#include <iostream>
#include <mpi.h>

#include "matrix_builder.hpp"
#include "pagerank_solver.hpp"

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const int N = 65536;
  const double p = 0.85;

  // Build the G matrix
  std::vector<MatrixEntry> G = build_sparse_matrix(rank, size, N);
  for (const auto& [row, col, val] : G) {
    std::cout << "Rank " << rank << " G(" << row << ", " << col << ") = " << val << "\n";
  }

  // Calculate solution vector u
  std::vector<double> u = run_power_method(G, N, rank, size, p);
  for (int i = 0; i < u.size(); ++i) {
    std::cout << "u[" << i << "]" << " = " << u.at(i) << "\n";
  }

  // Sort and rank on process 0

  MPI_Finalize();
  return 0;
}