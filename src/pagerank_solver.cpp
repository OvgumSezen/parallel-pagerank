#include "pagerank_solver.hpp"

#include <complex>
#include <mpi.h>
#include <numeric>

/**
 * Method that calculates the complete pagerank vector from the sparse matrix input
 * @param local_matrix := local sparse matrix G
 * @param N := total number of pages
 * @param rank := rank of the process
 * @param size := number of processes
 * @param p := damping factor (0.85)
 * @param max_iter := maximum number of iterations for convergence (1000)
 * @param tol := convergence tolerance (1e-10)
 * @return the final pagerank vector (computed in parallel but fully available at all ranks by design)
 */
std::vector<double> run_power_method(
    const std::vector<MatrixEntry>& local_matrix,
    int N,
    int rank,
    int size,
    double p,
    int max_iter,
    double tol) {
    std::vector<double> u(N, 1.0 / N);  // current pagerank vector initialized to uniform probability
    std::vector<double> u_next(N, 0.0); // pagerank vector used to accumulate probability in the next iteration

    std::vector<int> out_degree(N, 0);  // stores the information of how many outgoing links each page "i" has
    for (const auto& [i, j, val] : local_matrix) {
        out_degree[i]++;
    }   // the out-degree (r) is useful to normalize the transition probability (M) as follows: M(i, j) = G(i, j)/r(i)

    for (int iter = 0; iter < max_iter; ++iter) {
        std::fill(u_next.begin(), u_next.end(), 0.0); // clear u_next for the new iteration

        for (const auto& [i, j, val] : local_matrix) {
            if (out_degree[i] > 0) {
                const double M_ij = p * (val / out_degree[i]);
                u_next[j] +=  M_ij * u[i];
            }
        }   // this is the main calculation M_t * u where M := p(G(i, j)/r(i)) + (1-p)/N
            // note that u_t * M = u_T ==> M_t * u = u AND the teleportation factor (1-p)/N will be computed later

        std::vector<double> global_u_next(N);
        MPI_Allreduce(u_next.data(), global_u_next.data(), N, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
            // every process gets the full global_u_next (for symmetricity and ease of debugging)

        const double global_sum_u = std::accumulate(u.begin(), u.end(), 0.0);
        const double teleport = (1.0-p) * (global_sum_u / N);
        for (int i = 0; i < N; ++i) {
            global_u_next[i] += teleport;
        }   // added the teleportation factor needed for convergence
            // note that the global_sum_u is added to the teleportation factor to handle the dangling nodes

        double diff = 0.0;
        for (int i = 0; i < N; ++i) {
            diff += std::fabs(global_u_next[i] - u[i]);
        }   // calculate the L1-norm of the change in the pagerank vector value

        if (diff < tol) {
            break;
        }   // check for convergence

        std::swap(u, global_u_next);    // switch u_next with u for the next iteration
    }

    return u;
}