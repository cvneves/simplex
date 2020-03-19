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

    // printf("\n");
    // for (int i = 0; i < s->data->m; i++)
    // {
    //     printf("%g ", s->p[i]);
    // }
    // printf("\n");

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
        // printf("%g ", s->u[i]);
    }

    // printf("\n");
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

    // printf("%g\n", s->theta);

    for (int i = 0; i < s->data->m; i++)
    {
        s->x[s->basic_cols[i]] -= s->theta * s->u[i];
    }
    s->x[s->non_basic_cols[s->pivot_col_index]] = s->theta;

    for (int i = 0; i < s->data->n; i++)
    {
        // printf("%g ", s->x[i]);
    }
    // printf("\n");

    // printf("%d %d\n", s->non_basic_cols[s->pivot_col_index], s->basic_cols[s->pivot_row_index]);

    int temp = s->non_basic_cols[s->pivot_col_index];
    s->non_basic_cols[s->pivot_col_index] = s->basic_cols[s->pivot_row_index];
    s->basic_cols[s->pivot_row_index] = temp;

    // for(int i = 0; i < s->data->m ; i++)
    // {
    //     printf("%d ", s->basic_cols[i]);
    // }
    // printf("\n");

    for (int i = 0; i < s->data->m; i++)
    {
        if (i != s->pivot_row_index)
        {
            t_double row_coeff = s->u[i] / s->u[s->pivot_row_index];
            for (int j = 0; j < s->data->m; j++)
            {
                s->B_inv[i][j] -= row_coeff * s->B_inv[s->pivot_row_index][j];
            }
        }
        else
        {
            for (int j = 0; j < s->data->m; j++)
            {
                s->B_inv[i][j] /= s->u[s->pivot_row_index];
            }
        }
    }

    printf("\n");
    for (int i = 0; i < s->data->m; i++)
    {
        for (int j = 0; j < s->data->m; j++)
        {
            printf("%g ", s->B_inv[i][j]);
        }
        printf("\n");
    }
}

void SolveLinearProblem(Data *data)
{
    Simplex *s = malloc(sizeof(Simplex));
    InitializeSimplex(s, data);

    {
        // int bcols[] = {0, 2, 6};
        // int nbcols[] = {1, 3, 4, 5};
        // t_double B[3][3] = {{0.5, -0.5, 0}, {-0.5, 1.5, 0}, {-0.5, -2.5, 1}};
        int bcols[] = {4,5,6};
        int nbcols[] = {0,1,2,3};
        t_double B[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};

        for (int i = 0; i < data->n; i++)
        {
            s->x[i] = 0;
        }

        for (int i = 0; i < data->m; i++)
        {
            for (int j = 0; j < data->m; j++)
            {
                s->B_inv[i][j] = B[i][j];
                s->x[bcols[i]] += s->B_inv[i][j] * data->b[j];
            }
            s->basic_cols[i] = bcols[i];
        }

        for (int i = 0; i < data->n - data->m; i++)
        {
            s->non_basic_cols[i] = nbcols[i];
        }

        for (int i = 0; i < data->n; i++)
        {
            // printf("%g ", s->x[i]);
        }

        // printf("\n");
    }

    while (1)
    {
        if (SolvePricing(s) == -1)
        {
            break;
        }

        ComputeDirection(s);
        ComputeNewBasis(s);
    }

    t_double obj_value = 0;
    for (int i = 0; i < data->n; i++)
    {
        obj_value += s->x[i] * data->c[i];
    }

    printf("Obj value: %g\n", obj_value);

    DeleteSimplex(s);
}