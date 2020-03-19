#ifndef DATA_H
#define DATA_H

#include "MatrixUtils.h"

typedef struct Data
{
    int m, n;
    t_double **A;
    t_double *c, *b;

} Data;

void ReadData1(Data **data, char *file_name);
void DeleteData(Data *data);
void PrintData(Data *data);

#endif