#include <math.h>

// outputs squared error between y and yhat
double squared_error(double y, double yhat)
{
    return (y - yhat) * (y - yhat);
}

// outputs average squared error between y and yhat
double mean_squared_error(double *y, double *yhat, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += squared_error(y[i], yhat[i]);
    }
    return sum / size;
}

// calculate the step size of slope from single data
double MSE_slope_single_rate(double x, double y, double m, double b)
{
    // Derivative of (yhat - y) ^ 2 = 2 * (yhat - y) * x
    double yhat = m * x + b;
    return 2 * (yhat - y) * x;
}

// calculate the step size of slope from all data
double MSE_slope_learning_rate(double * x, double * y, int size, double m, double b)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum += MSE_slope_single_rate(x[i], y[i], m, b);
    return sum / size;
}

// calculate the step size of intercept from single data
double MSE_intercept_single_rate(double x, double y, double m, double b)
{
    // Derivative of (yhat - y) ^ 2 = 2 * (yhat - y)
    double yhat = m * x + b;
    return 2 * (yhat - y);
}

// calculate the step size of intercept from all data
double MSE_intercept_learning_rate(double * x, double * y, int size, double m, double b)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
        sum += MSE_intercept_single_rate(x[i], y[i], m, b);
    return sum / size;
}

