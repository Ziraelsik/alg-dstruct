#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#pragma once

enum error {
	null_list = 1,
};


typedef struct node_t {
	struct node_t* next;
	struct node_t* prev;
	char* str;
}node_t;

typedef struct {
	struct node_t* head;
} list_t;

list_t* create_list();

node_t* create_node(char* str);

node_t* push_element_list(list_t* list, char* str);

int  destroy_list(list_t* list);

void swap_str(node_t* a, node_t* b);

void bubble_sort_list(list_t* list);
