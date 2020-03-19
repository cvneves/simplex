#include "Simplex.h"

void InitializeSimplex(Simplex *simplex, Data *data)
{
    simplex->data = data;
    simplex->c_bar = malloc(data->n * sizeof(t_double));
    simplex->x = malloc(data->n * sizeof(t_double));
    simplex->u = malloc(data->m * sizeof(t_double));
    simplex->p = malloc(data->m * sizeof(t_double));
    simplex->B_inv = malloc(data->m * sizeof(t_double *));
    simplex->basic_cols = malloc(data->m * sizeof(int));

    for (int i = 0; i < data->n; i++)
    {
        simplex->c_bar[i] = data->c[i];
    }
    for (int i = 0; i < data->m; i++)
    {
        simplex->B_inv[i] = malloc(data->m * sizeof(t_double));
    }
}
void DeleteSimplex(Simplex *simplex)
{

    free(simplex->c_bar);
    free(simplex->x);
    free(simplex->u);
    free(simplex->p);
    free(simplex->basic_cols);

    for (int i = 0; i < simplex->data->m; i++)
    {
        free(simplex->B_inv[i]);
    }
    free(simplex->B_inv);

    free(simplex);
}

void ComputeReducedCosts(Simplex *s)
{
    //  Compute p'
    for (int j = 0; j < s->data->m; j++)
    {
        int i = s->basic_cols[j];

        s->p[j] = 0;
        for (int k = 0; k < s->data->m; k++)
        {
            s->p[j] += s->data->c[s->basic_cols[k]] * s->B_inv[k][j];
        }
    }

    printf("\n");
    for(int i = 0; i < s->data->m ;i++)
    {
        printf("%g ", s->p[i]);
    }
    printf("\n");

    for (int j = 0; j < s->data->n; j++)
    {
        for(int k = 0; k < s->data->m; k++)
        {
            s->c_bar[j] -= s->p[k] * s->data->A[k][j];
        }
    }

    printf("\n");
    for (int i = 0; i < s->data->n; i++)
    {
        printf("%g ", s->c_bar[i]);
    }
    printf("\n");
}
