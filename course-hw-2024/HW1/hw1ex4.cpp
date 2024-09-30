#include<iostream>
#include<iomanip>
#include<cmath>
#include<vector>

const double step_size = 1e-6;
const double tol = 1e-15;

double f(double x) {
    return sin(10*x) - x;
}

double bisect(double left, double right, double tol) {
    double mid = (left + right) / 2;
    
    while (std::abs(left-right) > tol){
        if (abs(f(mid)) <= tol) {
            return mid;
        }
        if (f(mid) * f(left) < 0) {
            right = mid;
        } else {
            left = mid;
        }
        mid = (left + right) / 2;
    }
}

std::vector<double> find_all_zeros(double left, double right, double step_size, double tol) {
    double zero;
    std::vector<double> zero_points;
    for (double new_left = left; (new_left + step_size) < right; new_left += step_size) {
        double new_right = new_left + step_size;
        if(f(new_left) * f(new_right) > 0) {
            continue;
        }
        else{
            zero = bisect(new_left, new_right, tol);
            zero_points.push_back(zero);
        }
        
    }
    return zero_points;
}

int main(int argv, char* argc[]) {
    double left = -1.0;
    double right = 1.0;
    std::vector<double> zero_points = find_all_zeros(left, right, step_size, tol);
    for (int i = 0; i < zero_points.size(); i++) {
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "Zero point " << i << " is at x = " << zero_points[i] << "." << std::endl;
    }
    return 0;
}