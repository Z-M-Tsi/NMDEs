#include<iostream>

double nested(double* coef[], double x)
{
	double result = *coef[0];
	for (int i = 1; coef[i] != nullptr; ++i){
		result = *coef[i] + result*x;
	}
	return result;
}

int main(int argc, char* argv[])
{
	double a = 1.0, b = 2.0, c = 3.0;
	double* coef[] = {&a, &b, &c, nullptr};
	double x = 2.0;

	double result = nested(coef, x);
	std::cout << "result = " << result << std::endl;
	
	return 0;
}
