#include "Data.h"

void ReadData1(Data **data, char *file_name)
{
    *data = malloc(sizeof(Data));

    FILE *f = fopen(file_name, "r");
    int m, n;

    fscanf(f, "%d %d", &n, &m);

    t_double *c = malloc(n * sizeof(t_double));
    for (int j = 0; j < n; j++)
    {
        fscanf(f, "%f", &c[j]);
    }

    t_double *b = malloc(m * sizeof(t_double));
    t_double **A = malloc(m * sizeof(t_double *));
    for (int i = 0; i < m; i++)
    {
        A[i] = malloc(n * sizeof(t_double));
        for(int j = 0; j < n; j++)
        {
            fscanf(f, "%f", &A[i][j]);
        }
        fscanf(f, "%f", &b[i]);
    }

    fclose(f);
    
    (*data)->n = n;
    (*data)->m = m;
    (*data)->A = A;
    (*data)->b = b;
    (*data)->c = c;


}
void DeleteData(Data *data)
{
    free(data->b);
    free(data->c);
    for(int i = 0; i < data->m; i++)
    {
        free(data->A[i]);
    }
    free(data->A);
    free(data);
}

void PrintData(Data *data)
{
    // printf("c = ");
    for(int i = 0; i < data->n; i++)
    {
        printf("%g ", data->c[i]);
    }
    printf("\n");
    // printf("\n A | b = \n");
    for(int i = 0; i < data->m; i++)
    {
        for(int j = 0; j < data->n; j++)
        {
            printf("%g ", data->A[i][j]);
        }
        printf(" %g\n", data->b[i]);
    }

}