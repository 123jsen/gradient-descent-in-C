#include <math.h>

// y: true value, yhat: predicted value
double squared_error(double y, double yhat)
{
    return (y - yhat) * (y - yhat);
}

// y: array of true values, yhat: array of predicted values
double mean_squared_error(double *y, double *yhat, int size)
{
    double sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += squared_error(y[i], yhat[i]);
    }
    return sum / size;
}

