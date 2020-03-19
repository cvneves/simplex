#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "MatrixUtils.h"
#include "Simplex.h"
#include "Data.h"

int main(int argc, char **argv)
{
    Data *data;
    ReadData1(&data, argv[1]);
    // PrintData(data);

    SolveLinearProblem(data);

    DeleteData(data);   

    exit(0);
}