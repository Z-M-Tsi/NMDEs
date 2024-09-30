#include<iostream>
#include <iomanip>
#include <cmath>

int nums[5] = {100, 1000, 10000, 100000, 1000000};
int nums_size = 5;

float sum_float[5];
float error_float[5];
float standard_sum_float = (float) M_PI*M_PI/6;

int main(int argc, char* argv[]) {
    
    std::cout << "==========>> FLOAT VERSION <<==========" << std::endl;
    for (int i = 0; i < nums_size ; i++) {
        sum_float[i] = 0;
        for (int j = nums[i]; j >= 1; j--){
            sum_float[i] += 1.0/(j*j);
        }
        error_float[i] = pow((sum_float[i] - standard_sum_float), 2);
    }

    for (int i = 0; i < nums_size ; i++) {
        std::cout << "For n = " << nums[i] << ", sum = " 
        << sum_float[i] << ", error = " << error_float[i] << std::endl;
    }

    return 0;
}