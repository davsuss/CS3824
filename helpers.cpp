#include "helpers.h"

void Matrix_init(Matrix * profile_matrix, int k) {
    profile_matrix->a = (int*)malloc(sizeof(int) * k);
    profile_matrix->t = (int*)malloc(sizeof(int) * k);
    profile_matrix->c = (int*)malloc(sizeof(int) * k);
    profile_matrix->g = (int*)malloc(sizeof(int) * k);
}

double LogLikelihood(Matrix * profile_matrix, Matrix * probability_matrix) {



    return 0;
}


