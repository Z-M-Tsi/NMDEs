#include<iostream>
#include<cmath>
#include<vector>
#include "../include/DenseMat/DenseMat.h"
#include <fstream>
#include<omp.h>

std::pair<int, double> triSOR(const int n, const std::vector<double>& b, double w, double tol, int max_iter);

int main(int argc, char const *argv[])
{
    double tol = 1e-8;
    int max_iter = 10000000;
    std::vector<int> n_values = {1000, 2000, 4000, 8000};

    // Open files to save results
    std::vector<std::ofstream> files(n_values.size());
    for (size_t i = 0; i < n_values.size(); i++) {
        std::string filename = "results_n_" + std::to_string(n_values[i]) + ".csv";
        files[i].open(filename);
        files[i] << "k,iterations\n"; // Write header
    }

    // Start parallel region
    #pragma omp parallel for collapse(2) schedule(dynamic)
    for (int i = 0; i < n_values.size(); i++){
        for (int k = 1; k <= 100; k++){
            double w = 1.0 + k/101.0;
            std::vector<double> bf(n_values[i]);
            for (int j = 0; j < n_values[i]; j++){
                bf[j] = 3.0*(j+1)*(1+(j+1)/n_values[i])*std::exp((j+1)/n_values[i])/std::pow(n_values[i], 3);
            }
            auto [iter, res] = triSOR(n_values[i], bf, w, tol, max_iter);
            // printf("SOR converged in %d iterations with residual %e\n", iter, res);

            // Write results to the corresponding CSV file
            #pragma omp critical
            {
                files[i] << k << "," << iter << "\n";
            }
        }
        
    }

    // Close the files
    for (auto& file : files) {
        file.close();
    }


    return 0;
}

std::pair<int, double> triSOR(const int n, const std::vector<double>& b, double w, double tol, int max_iter){
    std::vector<double> x(n, 1.0);
    std::vector<double> x_new(n, 1.0);
    double res = 1.0;
    int iter = 0;
    while (res > tol && iter < max_iter){
        x_new[0] = x[0] + w*(b[0] - 2*x[0] + x[1])/2;
        for (int i = 1; i < n-1; i++){
            x_new[i] = x[i] + w*(b[i] + x_new[i-1] - 2*x[i] + x[i+1])/2;
        }
        x_new[n-1] = x[n-1] + w*(b[n-1] + x_new[n-2] - 2*x[n-1])/2;

        res = 0.0;

        res += std::pow(2*x_new[0] - x_new[1] - b[0], 2);
        res += std::pow(2*x_new[n-1] - x_new[n-2] - b[n-1], 2);
        for (int i = 1; i < n-1; i++){
            res += std::pow(2*x_new[i] - x_new[i-1] - x_new[i+1] - b[i], 2);
        }
        res = std::sqrt(res);

        x = x_new;
        iter++;
    }
    if (iter == max_iter){
        std::cout << "SOR did not converge in limited iterations." << std::endl;
        std::cout << "Residual: " << res << std::endl;
    }
    return std::make_pair(iter, res);
}
