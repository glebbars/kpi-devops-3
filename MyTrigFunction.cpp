#include "MyTrigFunction.h"
#include <iostream>
#include <cmath> // For pow and tgamma

MyTrigFunction::MyTrigFunction() {}

// parameter 'n' determines the number of terms in the series to include in the summation
double MyTrigFunction::FuncA(int n) {
    double x = 1.0;
    double sum = 0.0;

    for (int i = 0; i <= n; ++i) {
        double numerator = (i % 2 == 0 ? 1.0 : -1.0) * tgamma(2 * i + 1);
        double denominator = pow(4, i) * pow(tgamma(i + 1), 2);
        sum += (numerator / denominator) * pow(x, i);
    }

    return sum;
}
