#ifndef HELPERS_H
#define HELPERS_H

#include <string.h>
#include "stdlib.h"

typedef struct _Matrix {
    int * a;
    int * t;
    int * g;
    int * c;
} Matrix;


void Matrix_init(Matrix * matrix, int k);

double LogLikelihood(Matrix * profile_matrix, Matrix * probability_matrix);

#endif