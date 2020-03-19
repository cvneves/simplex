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
    simplex->non_basic_cols = malloc((data->n - data->m) * sizeof(int));

    // for (int i = 0; i < data->n; i++)
    // {
    //     simplex->c_bar[i] = data->c[i];
    // }
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
    free(simplex->non_basic_cols);

    for (int i = 0; i < simplex->data->m; i++)
    {
        free(simplex->B_inv[i]);
    }
    free(simplex->B_inv);

    free(simplex);
}

int SolvePricing(Simplex *s)
{
    /* Compute p' */
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
    for (int i = 0; i < s->data->m; i++)
    {
        printf("%g ", s->p[i]);
    }
    printf("\n");

    s->pivot_col_index = -1;

    for (int i = 0; i < s->data->n - s->data->m; i++)
    {
        int j = s->non_basic_cols[i];
        s->c_bar[j] = s->data->c[j];

        /* Keep computing cj until a negative reduced cost is found */
        for (int k = 0; k < s->data->m; k++)
        {
            s->c_bar[j] -= s->p[k] * s->data->A[k][j];
        }
        if (s->c_bar[j] < -EPSILON)
        {
            s->pivot_col_index = i;
            return 0;
        }
    }

    /* There are no negative reduced costs, thus
    the current solution is optimal */
    if (s->pivot_col_index == -1)
    {
        return -1;
    }

    // printf("\n");
    // for (int i = 0; i < s->data->n - s->data->m; i++)
    // {
    //     int j = s->non_basic_cols[i];
    //     printf("%g ", s->c_bar[j]);
    // }
    // printf("\n");
}

void ComputeDirection(Simplex *s)
{
    int jth = s->non_basic_cols[s->pivot_col_index];

    for (int i = 0; i < s->data->m; i++)
    {
        s->u[i] = 0;

        for (int j = 0; j < s->data->m; j++)
        {
            s->u[i] += s->B_inv[i][j] * s->data->A[j][jth];
        }
        printf("%g ", s->u[i]);
    }

    printf("\n");
}

int ComputeNewBasis(Simplex *s)
{
    s->theta = INFINITY;
    for (int i = 0; i < s->data->m; i++)
    {
        if (s->u[i] > EPSILON)
        {
            t_double ratio = s->x[s->basic_cols[i]] / s->u[i];
            int smaller = s->theta + EPSILON < ratio;
            s->theta = smaller * s->theta + !smaller * ratio;
            s->pivot_row_index = smaller * s->pivot_row_index + !smaller * i;
        }
    }

    printf("%g\n", s->theta);

    for(int i = 0; i < s->data->m; i++)
    {
        s->x[s->basic_cols[i]] -= s->theta * s->u[i]; 
    }
    s->x[s->non_basic_cols[s->pivot_col_index]] = s->theta;

    for(int i = 0; i < s->data->n; i++)
    {
        printf("%g ", s->x[i]);
    }
    printf("\n");

    // printf("%d %d\n", s->non_basic_cols[s->pivot_col_index], s->basic_cols[s->pivot_row_index]);

    int temp = s->non_basic_cols[s->pivot_col_index];
    s->non_basic_cols[s->pivot_col_index] = s->basic_cols[s->pivot_row_index];
    s->basic_cols[s->pivot_row_index] = temp;

    // for(int i = 0; i < s->data->m ; i++)
    // {
    //     printf("%d ", s->basic_cols[i]);
    // }
    // printf("\n");

    for(int i = 0; i < s->data->m; i++)
    {
        
    }
}