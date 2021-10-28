#include "memallocator.h"

double mallocTest(LARGE_INTEGER frequency, int size) {
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    char* arr[MAX_ITERATIONS] = { NULL };
    int last_i = 0;
    QueryPerformanceCounter(&start);
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (rand() % 3 == 0 && arr[last_i] != NULL) {
            free(arr[last_i]);
            arr[last_i] = NULL;
        }
        else {
            arr[i] = (char*)malloc(size);
            last_i = i;
        }
    }
    QueryPerformanceCounter(&end);
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        free(arr[i]);
    }
    return (double)(end.QuadPart - start.QuadPart) /(double) frequency.QuadPart;
}
double memallocTest(LARGE_INTEGER frequency, int size) {
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    char* arr[MAX_ITERATIONS] = { NULL };
    int last_i = 0;
    QueryPerformanceCounter(&start);
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (rand() % 3 == 0 && arr[last_i] != NULL) {
            memfree(arr[last_i]);
            arr[last_i] = NULL;
        }
        else {
            arr[i] = (char*)memalloc(size);
            last_i = i;
        }
    }
    QueryPerformanceCounter(&end);
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        memfree(arr[i]);
    }
    return (double)(end.QuadPart - start.QuadPart) / (double)frequency.QuadPart;
}
int main(void) {
    setlocale(LC_ALL,"RUS");
    FILE *f = fopen(R"(C:\Users\User\Desktop\LabB\data.csv)", "w");
    if (f == NULL) {
        printf("Error opening file\n");
        exit(1);
    }
    LARGE_INTEGER frequency;
    double interval[2];
    QueryPerformanceFrequency(&frequency);
    fprintf(f, "malloc;memalloc\n");
    for (int i = 10; i < MAX_ALLOCATING_SIZE; i += 10) {
        interval[0] = mallocTest(frequency, i);
        interval[1] = memallocTest(frequency, i);
        fprintf(f, "%lf;%lf\n", interval[0], interval[1]);
    }
    fclose(f);
    memdone();
    return 0;
}






