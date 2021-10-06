#include "SourceA.h"

list_t* create_list() {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	if (list == NULL) {
		return NULL;
	}
	list->head = NULL;
	return list;
}

node_t* create_node(char* str) {
	if (str == NULL) {	
		return NULL;
	}
	node_t* node = (node_t*)malloc(sizeof(node_t));
	if (node == NULL) {
		return NULL;
	}
	node->str = str;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

node_t* push_element_list(list_t* list, char* str) {
	node_t* node = list->head;
	if (str == NULL) {
		return NULL;
	}
	if (node == NULL) {
		node = (node_t*)malloc(sizeof(node_t));
		if (node == NULL) {
			return NULL;
		}
		list->head = node;
		node->str = str;
		node->next = NULL;
		node->prev = NULL;
		return node;
	}

	node_t* prev_node;

	while (node != NULL) {
		prev_node = node;
		node = node->next;
	}

	node = (node_t*)malloc(sizeof(node_t));
	if (node == NULL) {
		return NULL;
	}

	prev_node->next = node;
	node->str = str;
	node->next = NULL;
	node->prev = prev_node;

	return node;
}

void swap_str(node_t* a, node_t* b) {
	if (a == NULL || b == NULL) {
		return;
	}
	char* temp = a->str;
	a->str = b->str;
	b->str = temp;
}

void bubble_sort_list(list_t* list) {
	if ((list == NULL )|| (list->head == NULL)) {
		return;
	}
	int flag = 1;
	node_t* node = NULL;
	node_t* node_next = NULL;

	while (flag) {
		node = list->head;
		node_next = node->next;
		flag = 0;
		while (node_next != NULL) {
			if (strcmp(node->str, node_next->str) > 0) {
				swap_str(node, node_next);
				flag = 1;
			}
			node = node_next;
			node_next = node->next;
		}
	}
}

int destroy_list(list_t* list) {
	if (list == NULL) {
		return null_list;
	}
	node_t* node = (node_t*)malloc(sizeof(node_t));
	node_t* next_node;
	if (node == NULL) {
		return null_list;
	}
	node = list->head;
	while (node != NULL) {
		next_node = node->next;
		free(node);
		node = next_node;
	}
	free(node);
	free(list);
	return 0;
}






