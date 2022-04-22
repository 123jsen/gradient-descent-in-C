#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "optimizers.h"

// Calculate the values of yhat using y=mx+b
void predict(double *x, double *yhat, int size, double m, double b)
{
	for (int i = 0; i < size; i++)
	{
		yhat[i] = m * x[i] + b;
	}
}

int main(int argc, char *argv[])
{
	// Flags for program
	int opt;
	int verbose = 0;

	// Arrays for data
	double *x = NULL;
	double *y = NULL;

	// Input Size
	int size = 0;

	// Hyperparameters
	double learn_rate = 0.001;
	int num_epochs = 10000;
	double m_slope = 1;
	double b_int = 0;

	while ((opt = getopt(argc, argv, "ht:ir:e:v")) != -1)
	{
		switch (opt)
		{
		case 'r':
			learn_rate = atof(optarg);
			break;

		case 'e':
			num_epochs = atoi(optarg);
			break;

		case 't':
			FILE *fptr;
			if ((fptr = fopen(optarg, "r")) == NULL)
			{
				// TODO: file input
				printf("Read from file not implemented yet. File: %s\n", optarg);
			}
			break;

		case 'i':
			// inputsize is size of manual input
			// size should be total size of data set
			// this allows user to input data as well as text
			int inputsize;

			printf("Size of data set: ");
			scanf("%d", &inputsize);
			printf("Input %d data pairs (x, y): \n", inputsize);

			if (x == NULL)
				x = malloc(inputsize * sizeof(double));
			else
				x = realloc(x, (size + inputsize) * sizeof(double));

			if (y == NULL)
				y = malloc(inputsize * sizeof(double));
			else
				y = realloc(y, (size + inputsize) * sizeof(double));

			for (int i = size; i < size + inputsize; i++)
			{
				scanf("%lf %lf", &x[i], &y[i]);
			}
			size += inputsize;
			break;

		case 'v':
			verbose = 1;
			break;

		case 'h':
		default:
			printf("--HELP--\n");
			printf("This program optimizes linear regression using gradient descent.\n");
			printf("Linear regression can be easily solved using linear algebra, but this is a fun exercise.\n");
			printf("-h : Print help instructions.\n");

			printf("\n--INPUT--\n");
			printf("-t <filename> : Read data from a text file.\n");
			printf("-i : Read data from a manual input.\n");

			printf("\n--HYPERPARAMETERS--\n");
			printf("-r <learning rate> : Specify learning rate (default: 0.001)\n");
			printf("-e <number of epochs> : Specify number of epochs (default: 10000)\n");
			exit(EXIT_SUCCESS);
		}
	}

	if (size == 0)
	{
		printf("Failed to read data\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < num_epochs; i++)
	{
		double *yhat = malloc(size * sizeof(double));
		predict(x, yhat, size, m_slope, b_int);

		if (verbose)
		{
			printf("Epoch: %d ", i);
			printf("Current guess: y=%lfx+%lf ", m_slope, b_int);
			printf("Cost (MSE): %lf\n", mean_squared_error(y, yhat, size));
		}

		m_slope -= learn_rate * MSE_slope_learning_rate(x, y, size, m_slope, b_int);
		b_int -= learn_rate * MSE_intercept_learning_rate(x, y, size, m_slope, b_int);
	}

	printf("Training Complete\n");
	printf("Model: y = %lfx + %lf\n", m_slope, b_int);

	return 0;
}