#include <math.h>

double sigmoid(double x)
{
	return 1 / (1 + pow(M_E, -x));
}

double delta(int n, int depth, double )