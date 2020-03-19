#ifndef SIMPLEX_H
#define SIMPLEX_H

#include "MatrixUtils.h"
#include "Data.h"

typedef struct Simplex
{
    Data *data;

    t_double *c_bar, *x, *u, *p;
    int *basic_cols, *non_basic_cols;
    t_double **B_inv;
    int pivot_col_index, pivot_row_index;
    t_double theta;

} Simplex;

void InitializeSimplex(Simplex *simplex, Data *data);
void DeleteSimplex(Simplex *simplex);

int SolvePricing(Simplex *s);
void ComputeDirection(Simplex *s);
int ComputeNewBasis(Simplex *s);

#endif