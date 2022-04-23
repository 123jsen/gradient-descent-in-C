// Multiple layers, single depth classifier
// Takes in 1D input (x, c) where c stands for class 

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	// Flags for program
	int opt;
	int verbose = 0;

	// Arrays for data
	double *x = NULL;
	char *class = NULL;

	// Input Size
	int size = 0;

	// Hyperparameters
	double learn_rate = 0.001;
	int num_epochs = 10000;
	int depth = 5;

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
			depth = atoi(optarg);
			break;

		case 't':
			FILE *fptr;
			if ((fptr = fopen(optarg, "r")) != NULL)
			{
				fscanf(fptr, "%d", &size);

				if (verbose)
					printf("Size of file (%s): %d\n", optarg, size);

				x = malloc(size * sizeof(double));
				class = malloc(size * sizeof(char));

				for (int i = 0; i < size; i++)
				{
					fscanf(fptr, "%lf %d", &x[i], &class[i]);

					if (verbose)
						printf("Read x: %lf class: %d\n", x[i], class[i]);
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

			if (x == NULL)
				x = malloc(inputsize * sizeof(double));
			else
				x = realloc(x, (size + inputsize) * sizeof(double));

			if (class == NULL)
				class = malloc(inputsize * sizeof(char));
			else
				class = realloc(class, (size + inputsize) * sizeof(char));

			for (int i = size; i < size + inputsize; i++)
			{
				scanf("%lf %d", &x[i], &class[i]);
			}
			size += inputsize;
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

	if (size <= 0)
	{
		printf("Failed to read data\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}