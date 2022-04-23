#include <stdlib.h>
#include <math.h>

#include "single_NN.h"

double sigmoid(double z)
{
	return 1 / (1 + pow(M_E, -z));
}

void forward_propagation(double *a_values, nn_model *model, double x)
{
	a_values[0] = x;

	for (int i = 1; i < model->depth; i++)
	{
		double z_i = model->weights[i] * a_values[i - 1] + model->biases[i];
		a_values[i] = sigmoid(z_i);
	}
}

void back_propagation(double *a_values, nn_model *model, double x, char y, double learn_rate)
{
	// computer del C / del a[L]
	double *delta = malloc(model->depth * sizeof(double));

	delta[model->depth - 1] = 2 * (a_values[model->depth - 1] - y);
	for (int i = model->depth - 2; i > 0; i--)
	{
		delta[i] = delta[i + 1] * a_values[i + 1] * (1 - a_values[i + 1]) * model->weights[i + 1];
	}

	// compute all weights
	for (int i = model->depth - 1; i > 0; i--)
	{
		double derivative = delta[i] * a_values[i] * (1 - a_values[i]) * a_values[i - 1];
		model->weights[i] -= learn_rate * derivative;
	}

	// compute all biases
	for (int i = model->depth - 1; i > 0; i--)
	{
		double derivative = delta[i] * a_values[i] * (1 - a_values[i]);
		model->biases[i] -= learn_rate * derivative;
	}

	free(delta);
}
