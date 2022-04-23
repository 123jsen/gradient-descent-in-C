extern struct nn_model;
typedef struct nn_model nn_model;

// Function prototypes:
double sigmoid(double x);

void forward_propagation(double * a_values, nn_model model, double x)