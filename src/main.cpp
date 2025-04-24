#include <algorithm>
#include <iostream>
#include <mpi.h>
#include <numeric>

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
  const std::vector<MatrixEntry> G = build_sparse_matrix(rank, size, N);

  // Calculate solution vector u
  std::vector<double> u = run_power_method(G, N, rank, size, p);

  // Sort and rank on process 0
  if (rank == 0) {
    std::vector<std::pair<int, double>> ranked;
    for (int i = 0; i < N; ++i)
      ranked.emplace_back(i, u[i]);

    std::sort(ranked.begin(), ranked.end(),
              [](auto& a, auto& b) { return b.second > a.second; });

    std::cout << "\nTop 10 pages:\n";
    for (int i = 0; i < 10; ++i) {
      std::cout << "Page " << ranked[i].first
                << " → Rank: " << ranked[i].second << "\n";
    }

    const double sum = std::accumulate(u.begin(), u.end(), 0.0);
    std::cout << "\nSum of rank vector: " << sum << " (should ≈ 1)\n";
  }

  MPI_Finalize();
  return 0;
}