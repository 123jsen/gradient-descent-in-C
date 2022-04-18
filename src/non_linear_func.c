#include <math.h>

double sigmoid(double x) {
	return 1 / (1 + pow(M_E, -x));
}

double relu(double x) {
	if (x <= 0)
		return 0;
	else
		return x;
}


