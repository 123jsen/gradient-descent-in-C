double squared_error(double y, double yhat);
double mean_squared_error(double *y, double *yhat, int size);

double MSE_slope_single_rate(double x, double y, double m, double b);
double MSE_slope_learning_rate(double * x, double * y, int size, double m, double b);
double MSE_intercept_single_rate(double x, double y, double m, double b);
double MSE_intercept_learning_rate(double * x, double * y, int size, double m, double b);