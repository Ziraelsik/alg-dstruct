#ifndef LABD_DOPF_H
#define LABD_DOPF_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define PLUS_RANGE(val) (((val) >= 0) ? (val): 0)
#pragma warning(disable:4996)

typedef struct {
    int l_t;
    int d_t;
    int w_t;
    int used_flag;
} Good;

int delivery_solver(Good *goods, unsigned N, unsigned K, unsigned int *ans);

void stress_test();

#endif //LABD_DOPF_H