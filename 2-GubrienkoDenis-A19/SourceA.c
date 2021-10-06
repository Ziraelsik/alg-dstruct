#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef enum {
	memory_error,
	null_string,
	null_list,
}error_t;

typedef struct node_t {
	struct node_t* next;
	struct node_t* prev;
	char* str;
}node_t;

typedef struct {
	struct node_t* head;
} list_t;


list_t* create_list() {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	if (list == NULL) {
		exit(memory_error);
	}
	list->head = NULL;

	return list;
}

node_t* create_node(char* str) {
	if (str == NULL) {
		exit(null_string);
	}
	node_t* nodes = (node_t*)malloc(sizeof(node_t));
	if (nodes == NULL) {
		exit(memory_error);
	}
	nodes->str = str;
	nodes->next = NULL;
	nodes->prev = NULL;
	return nodes;
}

void destroy_list(list_t* list) {
	if (list == NULL) {
		exit(null_list);
	}
	node_t* ptr = list->head;
	node_t* next_node = NULL;
	do {
		next_node = ptr->next;
		free(ptr);
		ptr = next_node;
	} while (ptr != NULL);
	free(ptr);
	free(list);
}

void add_element_list(node_t* node_s, char* str) {

	if (node_s == NULL) {
		exit(null_list);
	}
	if (str == NULL) {
		exit(null_string);
	}
	node_t* new_nodes = (node_t*)malloc(sizeof(node_t));

	if (new_nodes == NULL) {
		exit(memory_error);
	}
	new_nodes->str = (char*)malloc(strlen(str) + 1);
	if (new_nodes->str == NULL) {
		exit(memory_error);
	}
	strcpy(new_nodes->str, str);

	new_nodes->prev = node_s;
	new_nodes->next = NULL;
	node_s->next = new_nodes;
}

void swap_str(node_t* a, node_t* b) {
	if (a == NULL || b == NULL) {
		exit(null_string);
	}
	char* temp = a->str;
	a->str = b->str;
	b->str = temp;

}

void bubble_sort_list(list_t* list) {
	if (list == NULL || list->head == NULL) {
		exit(null_list);
	}
	int flag = 1;
	node_t* ptr = NULL;
	node_t* ptr_next = NULL;

	while (flag) {
		ptr = list->head;
		ptr_next = ptr->next;
		flag = 0;
		while (ptr_next != NULL) {
			if (strcmp(ptr->str, ptr_next->str) > 0) {
				swap_str(ptr, ptr_next);
				flag = 1;
			}
			ptr = ptr_next;
			ptr_next = ptr->next;
		}
	}
}

void print_list(list_t* list) {
	node_t* list_p = list->head;
	while (list_p != NULL) {
		printf("~%s \n", list_p->str);
		list_p = list_p->next;
	}
	printf("\n");
}

int main(void) {
	return 0;
}




