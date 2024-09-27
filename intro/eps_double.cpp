#include<iostream>

int main(int argc, char* argv[])
{
	double eps = 1.0;
	int count = 0;

	while (eps > 0)
	{
		count += 1;
		std::cout << "round " << count << ", eps = " << eps << std::endl;
		eps *= 0.5;

	}

	return 0;
}
