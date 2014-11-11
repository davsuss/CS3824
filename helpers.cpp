#include "helpers.h"

double LogLikelihood(char ** kmers, int num_kmers) {
    int i, j, k, *a, *t, *g, *c;
    
    k = strlen(*kmers);
    
    a = (int*) malloc(sizeof(int) * k);
    t = (int*) malloc(sizeof(int) * k);
    g = (int*) malloc(sizeof(int) * k);
    c = (int*) malloc(sizeof(int) * k);



    char * kmer;
    // Iterate through kmers and build profile matrix
    for (i = 0; i < num_kmers; ++i) {
        kmer = kmers[i];
        // Evaluate each position of kmer
        for (j = 0; j < k; ++j) {
            if (kmer[j] == 'a') {
                a[j]++;
            }
            else if (kmer[j] == 't') {
                t[j]++;
            }
            else if (kmer[j] == 'g') {
                g[j]++;
            }
            else if (kmer[j] == 'c') {
                c[j]++;
            }
        }
    }


    return 0;
}


