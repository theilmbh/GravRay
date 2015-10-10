#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

double* rk4(double* (*f)(double, double*, int), double *y0, double t0, int len, double dt)
{
    /* updates one RK4 step */
    double *f0;
    double *f1;
    double *f2;
    double *f3;
    
    double *k2;
    double *k3;
    double *k4;
    double *u;
    
    double t1, t2, t3;
    
    int i;
    f0 = f(t0, y0, len);
    
    t1 = t0 + dt / 2.0;
    k2 = malloc(len*sizeof(double));
    for(i=0; i<len; i++)
    {
        k2[i] = y0[i] + dt * f0[i] / 2.0;
    }
    f1 = f(t1, k2, len);
    
    t2 = t0 + dt / 2.0;
    k3 = malloc(len*sizeof(double));
    for(i=0; i<len; i++)
    {
        k3[i] = y0[i] + dt * f1[i] / 2.0;
    }
    f2 = f(t2, k3, len);
    
    t3 = t0 + dt;
    k4 = malloc(len*sizeof(double));
    for(i=0; i<len; i++)
    {
        k4[i] = y0[i] + dt*f2[i];
    }
    f3 = f(t3, k4, len);
    
    u = malloc(len*sizeof(double));
    for(i=0; i<len; i++)
    {
        u[i] = y0[i] + dt* (f0[i] + 2.0*f1[i] + 2.0*f2[i] + f3[i]) / 6.0;
    }
    
    free(f0);
    free(f1);
    free(f2);
    free(f3);
    free(k2);
    free(k3);
    free(k4);
    
    return u;

}

double* test_f(double t, double* state, int len)
{

    assert(len == 2); /* We're only dealing with 2D system atm */
    
    double* result;
    result = malloc(len*sizeof(double));
    
    result[0] = state[1];
    result[1] = -1.0 * state[0];
    
    return result;
}

int main()
{

    double y0[2] = {1.0, 0.0};
    double t0 = 0.0;
    int len = 2;
    double dt = 0.01;
    
    int n_step = (int)floor(2*3.14159 / dt);
    
    double **trajectory;
    double *step_result;
    int i;
    
    trajectory = malloc(n_step*sizeof(double*));
    for(i=0; i<n_step; i++)
    {
        trajectory[i] = calloc(n_step, len*sizeof(double));
    }
    
    int step;
    for(step=0; step<n_step; step++)
    {
        step_result = rk4(test_f, y0, t0, len, dt);
        printf("%f\n", step_result[0]);
        for(i=0; i<len; i++)
        {
            trajectory[step][i] = step_result[i];
            y0[i] = step_result[i];
        }
        free(step_result);
    }
    
    return 0;
}