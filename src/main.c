#include <stdio.h>
#include <stdlib.h>

#include "non_linear_func.h"

int main() {
    printf("Which function do you want to test? 1. Sigmoid 2. Relu\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 1)
    {
        double x;
        printf("Please input x: ");
        scanf("%lf", &x);
        printf("f(x) = %lf\n", sigmoid(x));
    }
    else if (choice == 2)
    {
        double x;
        printf("Please input x: ");
        scanf("%lf", &x);
        printf("f(x) = %lf\n", relu(x));
    }
}