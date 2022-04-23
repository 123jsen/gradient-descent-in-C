#include <math.h>
#include "single_NN.h"

double sigmoid(double z)
{
	return 1 / (1 + pow(M_E, -z));
}

void forward_propagation(double * a_values, nn_model * model, double x)
{
	a_values[0] = x;
	
	for (int i = 1; i < model->depth; i++)
	{
		double z_i = model->weights[i] * a_values[i-1] + model->biases[i];
		a_values[i] = sigmoid(z_i);
	}
}


