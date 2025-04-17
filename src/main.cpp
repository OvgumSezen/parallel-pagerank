#include <iostream>
#include <mpi.h>

#include "matrix_builder.hpp"

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  const int N = 65536;
  std::vector<MatrixEntry> entries = buildSparseMatrix(rank, size, N);

  for (const auto& [row, col, val] : entries) {
    std::cout << "Rank " << rank << " G(" << row << ", " << col << ") = " << val << "\n";
  }

  MPI_Finalize();
  return 0;
}