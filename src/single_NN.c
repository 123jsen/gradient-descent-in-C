// Multiple layers, single depth classifier
// Takes in 1D input (x, c) where c stands for class

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct nn_model
{
	int depth;
	double *weights;
	double *biases;
};

typedef struct nn_model nn_model;

struct input_data
{
	int size;
	double *x;
	char *class;
};

typedef struct input_data input_data;

// Sets default values of weights and biases
void initialize_model(nn_model * model)
{
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

	// Hyperparameters
	double learn_rate = 0.001;
	int num_epochs = 10000;

	// Declare variables
	nn_model *model = malloc(sizeof(nn_model));
	model->weights = NULL;
	model->biases = NULL;
	model->depth = 5;

	input_data *data = malloc(sizeof(input_data));
	data->size = 0;
	data->x = NULL;
	data->class = NULL;


	while ((opt = getopt(argc, argv, "ht:ir:e:d:v")) != -1)
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
				data->class = malloc(data->size * sizeof(char));

				for (int i = 0; i < data->size; i++)
				{
					fscanf(fptr, "%lf %d", &data->x[i], &data->class[i]);

					if (verbose)
						printf("Read x: %lf class: %d\n", data->x[i], data->class[i]);
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

			if (data->class == NULL)
				data->class = malloc(inputsize * sizeof(char));
			else
				data->class = realloc(data->class, (data->size + inputsize) * sizeof(char));

			for (int i = data->size; i < data->size + inputsize; i++)
			{
				scanf("%lf %d", &data->x[i], &data->class[i]);
			}
			data->size += inputsize;
			break;

		case 'v':
			verbose = 1;
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
			printf("-v : Verbose mode.\n");

			printf("\n--HYPERPARAMETERS--\n");
			printf("-r <learning rate> : Specify learning rate (default: 0.001)\n");
			printf("-e <number of epochs> : Specify number of epochs (default: 10000)\n");
			printf("-d <network depth> : Specify number of neurons (default: 5)\n");
			exit(EXIT_SUCCESS);
		}
	}

	if (data->size <= 0)
	{
		printf("Failed to read data\n");
		exit(EXIT_FAILURE);
	}

	initialize_model(&model);

	return 0;
}