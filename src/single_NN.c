// Multiple layers, single depth classifier
// Takes in 1D input (x, c) where c stands for class

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "single_NN.h"
#include "optimizers.h"
#include "non_linear_func.h"

// Sets default values of weights and biases
void initialize_model(nn_model * model)
{
	model->weights = malloc(model->depth * sizeof(double));
	model->biases = malloc(model->depth * sizeof(double));

	for (int i = 0; i < model->depth; i++)
	{
		model->biases[i] = 1;
		model->weights[i] = 1;
	}
}

int main(int argc, char *argv[])
{
	// Flags for program
	int opt;
	int verbose = 0;
	int predict_mode = 0;

	// Hyperparameters
	double learn_rate = 0.5;
	int num_epochs = 20000;

	// Declare variables
	nn_model *model = malloc(sizeof(nn_model));
	model->weights = NULL;
	model->biases = NULL;
	model->depth = 5;

	input_data *data = malloc(sizeof(input_data));
	data->size = 0;
	data->x = NULL;
	data->cat = NULL;


	while ((opt = getopt(argc, argv, "ht:ir:e:d:vp")) != -1)
	{
		switch (opt)
		{
		case 'r':
			learn_rate = atof(optarg);
			break;

		case 'e':
			num_epochs = atoi(optarg);
			break;

		case 'd':
			model->depth = atoi(optarg);
			break;

		case 't':
			FILE *fptr;
			if ((fptr = fopen(optarg, "r")) != NULL)
			{
				fscanf(fptr, "%d", &data->size);

				if (verbose)
					printf("Size of file (%s): %d\n", optarg, data->size);

				data->x = malloc(data->size * sizeof(double));
				data->cat = malloc(data->size * sizeof(char));

				for (int i = 0; i < data->size; i++)
				{
					fscanf(fptr, "%lf %d", &data->x[i], &data->cat[i]);

					if (verbose)
						printf("Read x: %lf class: %d\n", data->x[i], data->cat[i]);
				}

				printf("Closing file...\n\n");
				fclose(fptr);
			}
			else
			{
				printf("Failed to read from file: %s\n", optarg);
				exit(EXIT_FAILURE);
			}
			break;

		case 'i':
			// inputsize is size of manual input
			// size should be total size of data set
			// this allows user to input data as well as text
			int inputsize;

			printf("Size of data set: ");
			scanf("%d", &inputsize);
			printf("Input %d data pairs (x, c): \n", inputsize);

			if (data->x == NULL)
				data->x = malloc(inputsize * sizeof(double));
			else
				data->x = realloc(data->x, (data->size + inputsize) * sizeof(double));

			if (data->cat == NULL)
				data->cat = malloc(inputsize * sizeof(char));
			else
				data->cat = realloc(data->cat, (data->size + inputsize) * sizeof(char));

			for (int i = data->size; i < data->size + inputsize; i++)
			{
				if (verbose) printf("(%d)-th pair: ", i - data->size);
				scanf("%lf %d", &data->x[i], &data->cat[i]);
			}
			data->size += inputsize;
			break;

		case 'v':
			verbose = 1;
			break;

		case 'p':
			predict_mode = 1;
			break;

		case 'h':
		default:
			printf("--HELP--\n");
			printf("This program uses a single height neural network to classify data\n");
			printf("Each data pair is a real number x and a class c (either 0 or 1)\n");
			printf("-h : Print help instructions.\n");

			printf("\n--INPUT--\n");
			printf("-t <filename> : Read data from a text file.\n");
			printf("-i : Read data from a manual input.\n");

			printf("\n--TESTING--\n");
			printf("-v : Verbose mode.\n");
			printf("-p : Allows testing by predictions after training is complete.\n");

			printf("\n--HYPERPARAMETERS--\n");
			printf("-r <learning rate> : Specify learning rate (current: %lf)\n", learn_rate);
			printf("-e <number of epochs> : Specify number of epochs (current: %d)\n", num_epochs);
			printf("-d <network depth> : Specify number of layers, including input and output. (current: %d)\n", model->depth);
			exit(EXIT_SUCCESS);
		}
	}

	if (data->size <= 0)
	{
		printf("Failed to read data\n");
		exit(EXIT_FAILURE);
	}
	
	initialize_model(model);

	if (verbose) printf("Model successfully initialized\n");

	// We will adopt online learning (i.e. one data at a time)

	// Move activation value array declaration outside of for loop
	// No need to free each time
	double * a_values = malloc (model->depth * sizeof(double));

	double error;
	for (int i = 0; i < num_epochs; i++)
	{
		if (verbose) printf("Epoch %d: ", i);

		error = 0;
		for (int j = 0; j < data->size; j++)
		{
			forward_propagation(a_values, model, data->x[j]);
			error += squared_error(a_values[model->depth - 1], data->cat[j]);

			back_propagation(a_values, model, data->x[j], data->cat[j], learn_rate);
		}	
		
		error /= data->size;
		if (verbose) printf("MSE: %lf\n", error);
	}

	printf("Training Complete\n");
	printf("MSE: %lf\n", error);

	printf("Final model configuration:\n");
	printf("Layer 0: input layer\n");
	for (int i = 1; i < model->depth; i++)
	{
		printf("Layer %d: weight: %lf, bias: %lf\n", i, model->weights[i], model->biases[i]);
	}

	if (predict_mode)
	{
		printf("\nPrediction mode:\n");

		int test_size = 0;
		printf("Testing data size:");
		scanf("%d", &test_size);

		for (int i = 0; i < test_size; i++)
		{
			double x;
			printf("Enter the x input: ");
			scanf("%lf", &x);

			double * a_values = malloc (model->depth * sizeof(double));
			forward_propagation(a_values, model, x);
			printf("Model output: %lf\n", a_values[model->depth - 1]);
			free(a_values);
		}

	}

	return 0;
}