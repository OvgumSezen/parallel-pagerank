#pragma once

#include "COOMatrix.hpp"

class Graph {
    public:
        int node_count;
        COOMatrix adjacency;

        explicit Graph(int N);
        void add_link(int from, int to);
        COOMatrix build_transition_matrix(double p) const;
        static Graph build_synthetic_graph(int N);
};
