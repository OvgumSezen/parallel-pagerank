#include <mpi.h>

#include "include/Graph.hpp"
#include "include/Measurement.hpp"
#include "include/PageRankSolver.hpp"
#include "include/PageRankSolverMPI.hpp"

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 4096;
    const Graph g = Graph::build_synthetic_graph(N);
    const COOMatrix M = g.build_transition_matrix(0.85);

    constexpr double t1_baseline = 0.0;
    Measurement meas(t1_baseline);

    meas.start();
    std::vector<double> ranks = PageRankSolverMPI::solve(M);
    meas.stop();
    meas.gather();
    meas.print(rank, size);
    meas.log_csv(rank, size);

    MPI_Finalize();
    return 0;
}
