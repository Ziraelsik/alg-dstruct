#include "gtest/gtest.h"
#include "pch.h"
extern "C" {
#include "SourceA.h"
#include <malloc.h>
}

TEST(create_list_test, creating_list_expect_head) {
	list_t* list = create_list();
	EXPECT_TRUE(list->head == NULL);
	EXPECT_TRUE(list != NULL);
	free(list);
}

TEST(create_node_test, creating_node_from_string) {
	char* str = "string";
	node_t* node = create_node(str);
	EXPECT_EQ(NULL, node->next);
	EXPECT_EQ(NULL, node->prev);
	EXPECT_EQ(node->str, str);
	EXPECT_TRUE(node != NULL);
	free(node);
}

TEST(create_node_test, creating_node_from_empty_string) {
	char* str = NULL;
	node_t* node = create_node(str);
	EXPECT_TRUE(NULL == node);
	free(node);
}


TEST(swap_str_test, swap_the_value_of_string) {
	node_t node1, node2;
	node1.str = "str1";
	node2.str = "str2";
	swap_str(&node1, &node2);
	EXPECT_TRUE(node1.str = "str2");
	EXPECT_TRUE(node2.str = "str1");
}

TEST(bubble_sort_list_test, sort_the_sorted_list) {
	list_t list;
	node_t node1, node2, node3;
	list.head = &node1;

	char* str1 = "string1";
	char* str2 = "string2";
	char* str3 = "string3";


	node1.str = str1;
	node1.next = &node2;
	node1.prev = NULL;

	node2.str = str2;
	node2.next = &node3;
	node2.prev = &node1;

	node3.str = str3;
	node3.next = NULL;
	node3.prev = &node2;

	bubble_sort_list(&list);

	EXPECT_TRUE(strcmp(node1.str, str1) == 0);
	EXPECT_TRUE(strcmp(node2.str, str2) == 0);
	EXPECT_TRUE(strcmp(node3.str, str3) == 0);
}

TEST(bubble_sort_list_test, sort_the_list_with_different_element_equal_lengths) {
	list_t list;
	node_t node1, node2, node3;
	list.head = &node1;

	char* str1 = "string5";
	char* str2 = "string2";
	char* str3 = "string1";


	node1.str = str1;
	node1.next = &node2;
	node1.prev = NULL;

	node2.str = str2;
	node2.next = &node3;
	node2.prev = &node1;

	node3.str = str3;
	node3.next = NULL;
	node3.prev = &node2;

	bubble_sort_list(&list);

	EXPECT_TRUE(strcmp(node1.str, str3) == 0);
	EXPECT_TRUE(strcmp(node2.str, str2) == 0);
	EXPECT_TRUE(strcmp(node3.str, str1) == 0);
}

TEST(bubble_sort_list_test, sort_the_list_with_different_element_different_lengths) {
	list_t list;
	node_t node1, node2, node3, node4;
	list.head = &node1;

	char* str1 = "sbri";
	char* str2 = "string";
	char* str3 = "strin";
	char* str4 = "atr";

	node1.str = str1;
	node1.next = &node2;
	node1.prev = NULL;

	node2.str = str2;
	node2.next = &node3;
	node2.prev = &node1;

	node3.str = str3;
	node3.next = &node4;
	node3.prev = &node2;

	node4.str = str4;
	node4.next = NULL;
	node4.prev = &node3;

	bubble_sort_list(&list);

	EXPECT_TRUE(strcmp(node1.str, str4) == 0);
	EXPECT_TRUE(strcmp(node2.str, str1) == 0);
	EXPECT_TRUE(strcmp(node3.str, str3) == 0);
	EXPECT_TRUE(strcmp(node4.str, str2) == 0);
}

TEST(bubble_sort_list_test, sort_the_list_with_same_element) {

	list_t list;
	node_t node1, node2, node3;
	list.head = &node1;

	char* str1 = "string";
	char* str2 = "string";
	char* str3 = "string";

	node1.str = str1;
	node1.next = &node2;
	node1.prev = NULL;

	node2.str = str2;
	node2.next = &node3;
	node2.prev = &node1;

	node3.str = str3;
	node3.next = NULL;
	node3.prev = &node2;

	bubble_sort_list(&list);

	EXPECT_TRUE(strcmp(node1.str, str1) >= 0);
	EXPECT_TRUE(strcmp(node2.str, str2) >= 0);
	EXPECT_TRUE(strcmp(node3.str, str3) >= 0);
}

TEST(push_element_list_test, push_element_to_empty_list) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	node_t* node = (node_t*)malloc(sizeof(node_t));
	assert(!(list == NULL));
	assert(!(node == NULL));
	char* str = "str";
	list->head = NULL;
	node = push_element_list(list, str);
	EXPECT_TRUE(node->str == str);
	EXPECT_TRUE(list->head == node);
	EXPECT_TRUE(node->next == NULL);
	EXPECT_TRUE(node->prev == NULL);
	free(list);
	free(node);
}

TEST(push_element_list_test, push_element_with_empty_string) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	node_t* node = (node_t*)malloc(sizeof(node_t));
	assert(!(list == NULL));
	assert(!(node == NULL));
	char* str = NULL;
	list->head = NULL;
	node = push_element_list(list, str);
	EXPECT_TRUE(node == NULL);
	EXPECT_TRUE(list->head == node);
	free(list);
	free(node);
}

TEST(push_element_list_test, push_element_to_list) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	node_t* node2 = (node_t*)malloc(sizeof(node_t));
	assert(!(list == NULL));
	assert(!(node1 == NULL));
	assert(!(node2 == NULL));
	char* str = "str2";

	list->head = (node_t*)malloc(sizeof(node_t));
	assert(!(list->head == NULL));
	
	node1->str = "str1";
	node1->next = NULL;
	node1->prev = NULL;
	list->head = node1;
	
	node2 = push_element_list(list, str);

	EXPECT_TRUE(list->head == node1);
	EXPECT_TRUE(node1->next == node2);
	EXPECT_TRUE(node2->str == str);
	EXPECT_TRUE(node2->prev == node1);
	EXPECT_TRUE(node2->next == NULL);
	free(node2);
	free(node1);
	free(list);
}

TEST(destroy_list_test, destroy_empty_list) {
    list_t* list = NULL;
	int flag = destroy_list(list);
	EXPECT_TRUE(flag == null_list);
}

TEST(destroy_list_test, destroy_list_with_one_element) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	node_t* node = (node_t*)malloc(sizeof(node_t));

	assert(!(list== NULL));
	assert(!(node == NULL));
	assert(!(list->head == NULL));

	list->head = node;
	node->str = "string";
	node->next = NULL;
	node->prev = NULL;


	int flag = destroy_list(list);
	EXPECT_TRUE(flag == 0 );
}

TEST(destroy_list_test, destroy_list_from_several_elements) {
	list_t* list = (list_t*)malloc(sizeof(list_t));
	node_t* node1 = (node_t*)malloc(sizeof(node_t));
	node_t* node2 = (node_t*)malloc(sizeof(node_t));

	assert(!(list == NULL));
	assert(!(node1 == NULL));
	assert(!(node2 == NULL));

	list->head = (node_t*)malloc(sizeof(node_t));

	assert(!(list->head == NULL));

	list->head = node1;

	node1->str = "str1";
	node1->next = node2;
	node1->prev = NULL;

	node2->str = "str2";
	node2->next = NULL;
	node2->prev = node1;

	int flag = destroy_list(list);
	EXPECT_TRUE(flag == 0);
}




