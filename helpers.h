#ifndef HELPERS_H
#define HELPERS_H

#include <string.h>
#include "stdlib.h"

double LogLikelihood(char ** kmers, int num_kmers);

typedef struct _ProfileMatrix {
    int * a;
    int * t;
    int * g;
    int * c;
} ProfileMatrix;



#endif