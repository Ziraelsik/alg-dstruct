#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#pragma warning(disable: 4996)

/*
 * CPU: Intel(R) Core(TM) i5-9300H 2.40 GHz
 * RAM: 7,85 GB
 * HDD: 930 GB
 *
 * Vertecies amount: 30000
 *      Stress Test results:
 *      Memory: 2.2 GB
 *      DFS execution time: 24.044000 seconds
 */

typedef struct {
    int number_vertex;
    int count_nearby_vertex;
    int *list_nearby_vertex;
} list_t;

//Создаём списки смежности
list_t *create_list(int amount_vertex) {
    list_t *list = malloc(sizeof(list_t) * amount_vertex);
    assert(list != NULL);
    for (int i = 0; i < amount_vertex; i++) {
        list[i].number_vertex = i;
        list[i].list_nearby_vertex = NULL;
        list[i].count_nearby_vertex = 0;
    }
    return list;
}

//Очищаем списки смежности
void free_list(list_t *list, int amount_vertex) {
    for (int i = 0; i < amount_vertex; i++) {
        free(list[i].list_nearby_vertex);
    }
    free(list);
}

//Выводим список вершин в порядке обхода в глубину
void print_vertex(int *result_list_vertex, int result_count) {
    for (int i = 0; i < result_count; i++) {
        printf("%d ", result_list_vertex[i]);
    }
}

//Добавление в список смежности вершину
void append_vertex(list_t *list, int i, int vertex) {
    if (list[i].list_nearby_vertex == NULL) {
        list[i].list_nearby_vertex = malloc(sizeof(int));
        list[i].list_nearby_vertex[0] = vertex;
        list[i].count_nearby_vertex++;
    } else {
        int count = list[i].count_nearby_vertex + 1;
        list[i].list_nearby_vertex = realloc(list[i].list_nearby_vertex, sizeof(int) * count);
        assert(list[i].list_nearby_vertex != NULL);
        list[i].list_nearby_vertex[count - 1] = vertex;
        list[i].count_nearby_vertex++;
    }
}

//Чтение входных данных
void read_nodes(list_t *list, int amount_vertex) {
    int vertex;
    char space;
    for (int i = 0; i < amount_vertex; i++) {
        //Номер вершины
        scanf("%d%c", &vertex, &space);
        list[i].number_vertex = vertex;
        //Номера смежных вершин к данной
        while (space == ' ') {
            scanf("%d%c", &vertex, &space);
            append_vertex(list, i, vertex);
            append_vertex(list, vertex, i);
        }
    }
}

//Наличие в списке смежности вершины
int checking_graph(int *list_nearby_vertex, int vertex, int count_nearby_vertex) {
    for (int i = 0; i < count_nearby_vertex; i++) {
        if (list_nearby_vertex[i] == vertex) {
            return 0;
        }
    }
    return vertex;
}

//Обход графа в глубину
void DFS(list_t *list, int amount_vertex, int vertex, int *result_list_vertex, int *result_count) {
    for (int i = 0; i < list[vertex].count_nearby_vertex; i++) {
        int new_vertex = checking_graph(result_list_vertex, list[vertex].list_nearby_vertex[i], *result_count);
        if (new_vertex != 0) {
            result_list_vertex[*result_count] = new_vertex;
            (*result_count)++;
            DFS(list, amount_vertex, new_vertex, result_list_vertex, result_count);
        }
    }
}



void stress_test(int amount_vertex) {
    list_t *list = create_list(amount_vertex);
    int width = 30;
//    printf("%i\n", amount_vertex);
    for (int i = 0; i < amount_vertex; i++) {
//        printf("%i: ", list[i].number_vertex);
        for (int j = 0; j < width; j++) {
            append_vertex(list, i, j);
            append_vertex(list, j, i);
//            printf("%i ", list[i].list_nearby_vertex[j]);
        }
//        printf("\n");
    }
    int *result_list_vertex = NULL;
    result_list_vertex = malloc(sizeof(int) * amount_vertex);
    assert(result_list_vertex != NULL);
    result_list_vertex[0] = 0;
    int result_count = 1;
    int start = 0;
    unsigned long start_time = clock();
    DFS(list, amount_vertex, start, result_list_vertex, &result_count);
    double time = (double) (clock() - start_time) / CLOCKS_PER_SEC;
//     printf("%lf", time);
    free(list);
    free(result_list_vertex);

}



int main(void) {
    //stress_test(30000);
    
    int amount_vertex = 0;
    assert(scanf("%d", &amount_vertex) > 0);

    list_t *list = NULL;
    list = create_list(amount_vertex);
    read_nodes(list, amount_vertex);

    int *result_list_vertex = NULL;
    result_list_vertex = malloc(sizeof(int) * amount_vertex);
    assert(result_list_vertex != NULL);

    result_list_vertex[0] = 0;
    int result_count = 1;
    int start = 0;

    DFS(list, amount_vertex, start, result_list_vertex, &result_count);
    print_vertex(result_list_vertex, result_count);

    free_list(list, amount_vertex);
    free(result_list_vertex);
    

    return 0;
}
