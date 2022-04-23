# gradient-descent-in-C

This project tries to implement what I've learnt in machine learning to C. My goals are:

1. Linear Regression using Gradient Descent
2. Train an NN with single neuron at each layer
3. Simple Neural Network with no constraints

## Linear Regression

For the objective and implementation of Linear Regression, read `grad_descent_on_regression.md`.
To compile, run the following commands inside `/src`.

```
gcc linear_regression.c optimizers.c -c
gcc linear_regression.o optimizers.o -o main
```

You can know the parameters of `main` by calling `main -h`.

## Single Height Classification Network

To compile, run the following commands inside `/src`.

```
gcc single_NN.c non_linear_func.c optimizers.c -c
gcc single_NN.o non_linear_func.o optimizers.o -o main
```

You can know the parameters of `main` by calling `main -h`.
