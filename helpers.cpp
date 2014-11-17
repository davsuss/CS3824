#include "helpers.h"

void Matrix_init(Matrix * profile_matrix, int k) {
    profile_matrix->a = (int*)malloc(sizeof(int) * k);
    profile_matrix->t = (int*)malloc(sizeof(int) * k);
    profile_matrix->c = (int*)malloc(sizeof(int) * k);
    profile_matrix->g = (int*)malloc(sizeof(int) * k);
}

double LogLikelihood(Matrix * profile_matrix, Matrix * probability_matrix, char * motif, int n) {
    int i, prof;
    double prob;
    double ll = 0;
    int len = strlen(motif);
    for (i = 0; i < len; i++) {
        if (motif[i] == '*') {
            continue;
        }
        else if (motif[i] == 'A') {
            prof = profile_matrix->a[i];
            prob = probability_matrix->a[0];
        }
        else if (motif[i] == 'T') {
            prof = profile_matrix->t[i];
            prob = probability_matrix->t[0];
        }
        else if (motif[i] == 'G') {
            prof = profile_matrix->g[i];
            prob = probability_matrix->g[0];
        }
        else if (motif[i] == 'C') {
            prof = profile_matrix->c[i];
            prob = probability_matrix->c[0];
        }
        ll += ((prof / n) / prob);
    }
    return ll;
}


