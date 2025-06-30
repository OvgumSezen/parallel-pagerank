#include "include/Measurement.hpp"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <mpi.h>

Measurement::Measurement(const double t1_baseline) : t1(t1_baseline) {}

void Measurement::start() {
    local_start = MPI_Wtime();
}

void Measurement::stop() {
    local_end = MPI_Wtime();
    local_elapsed = local_end - local_start;
}

void Measurement::gather() {
    MPI_Reduce(&local_elapsed, &max_elapsed, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
}

void Measurement::print(const int rank, const int size) const {
    if (rank == 0) {
        const double speedup = t1 / max_elapsed;
        const double efficiency = speedup / size;
        double kuck_function = speedup * efficiency;

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "=== Parallel Performance Metrics ===\n";
        std::cout << "Processes   : " << size << "\n";
        std::cout << "Time        : " << max_elapsed << " sec\n";
        std::cout << "Speedup     : " << speedup << "\n";
        std::cout << "Efficiency  : " << efficiency << "\n";
        std::cout << "Kuck Func   : " << kuck_function << "\n\n";
    }
}

void Measurement::log_csv(const int rank, const int size, const std::string& filename) const {
    if (rank == 0) {
        std::ofstream fout(filename, std::ios::app);
        fout << size << "," << max_elapsed << "," << (t1 / max_elapsed) << ","
             << (t1 / max_elapsed) / size << "," << (t1 / max_elapsed) * ((t1 / max_elapsed) / size) << "\n";
        fout.close();
    }
}