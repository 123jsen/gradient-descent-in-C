# Gradient Descent on Regression Parameters

## Objective

Suppose we are provided a matrix of real inputs and outputs, where the n-th pair is denote as (x<sub>n</sub>, y<sub>n</sub>). We are given an initial guess: y = m<sub>0</sub>x + b<sub>0</sub>. The algorithm should produce new values m<sub>i</sub> and b<sub>i</sub> according to gradient descent. Assume that we are using mean-squared error (MSE), but the logic is the same for other measures of error. Denote the cost of the output as C.

## Details

We need to find &part;C/&part;m and &part;C/&part;b. Using functions in `optimizers.c` to calculate the derivative, we will adjust m and b by its rate times m or b.
