#include "MyTrigFunction.h"
#include <iostream>

MyTrigFunction::MyTrigFunction() {}

double MyTrigFunction::FuncA() {
    double x = 1.0;
    double sum = 0.0;

    for (int i = 0; i < 3; ++i) {
        double numerator = (i % 2 == 0 ? 1.0 : -1.0) * tgamma(2 * i + 1);
        double denominator = pow(4, i) * pow(tgamma(i + 1), 2);
        sum += (numerator / denominator) * pow(x, i);
    }

    return sum;
}
