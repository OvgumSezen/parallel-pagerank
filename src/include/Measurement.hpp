#pragma once
#include <string>

class Measurement {
    double local_start = 0.0;
    double local_end = 0.0;
    double local_elapsed = 0.0;
    double max_elapsed = 0.0;
    double t1;


    public:
        Measurement(double t1_baseline);
        void start();
        void stop();
        void gather();
        void print(int rank, int size) const;
        void log_csv(int rank, int size, const std::string& filename = "measurements.csv") const;
};
