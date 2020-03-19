#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "MatrixUtils.h"
#include "Data.h"

typedef struct Simplex
{
    Data *data;

    t_double *c_bar, *x, *u, *p;
    int *basic_cols;
    t_double **B_inv;

} Simplex;

void InitializeSimplex(Simplex *simplex, Data *data);
void DeleteSimplex(Simplex *simplex);

void ComputeReducedCosts(Simplex *s);

#endif