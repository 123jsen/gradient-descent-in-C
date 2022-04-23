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
	char *cat;
};

typedef struct input_data input_data;