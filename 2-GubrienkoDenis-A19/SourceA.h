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

list_t* create_list();

node_t* create_node(char* str);
void destroy_list(list_t* list);
void add_element_list(node_t* node_s, char* str);
void swap_str(node_t* a, node_t* b);
void bubble_sort_list(list_t* list);