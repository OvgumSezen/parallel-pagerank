#include "include/Graph.hpp"

Graph::Graph(const int N) : node_count(N), adjacency(N, N) {}

void Graph::add_link(const int from, const int to) {
    adjacency.add_entry(from, to, 1.0);
}

COOMatrix Graph::build_transition_matrix(double p) const {
    std::vector outDegree(node_count, 0);
    for (const int rowIndex : adjacency.row_indices) {
        outDegree[rowIndex]++;
    }

    COOMatrix M(node_count, node_count);
    for (size_t k = 0; k < adjacency.values.size(); ++k) {
        const int i = adjacency.row_indices[k];
        const int j = adjacency.col_indices[k];
        const double prob = (outDegree[i] == 0) ? 1.0 / node_count : adjacency.values[k] / outDegree[i];
        M.add_entry(j, i, p * prob);  // transpose for right multiplication
    }

    for (int i = 0; i < node_count; ++i) {
        for (int j = 0; j < node_count; ++j) {
            M.add_entry(i, j, (1.0 - p) / node_count);
        }
    }

    return M;
}

Graph Graph::build_synthetic_graph(const int N) {
    Graph g(N);

    for (int j = 1; j < N; ++j)
        g.add_link(j - 1, j);

    for (int i = 2; i < N; ++i)
        g.add_link(i, 1);

    return g;
}
