#pragma warning (disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct tree_t {
    struct tree_t *left;
    struct tree_t *right;
    int value;
    int width;
} tree_t;

void tree_insert_node(tree_t **tree, tree_t *new_node) {
    if (new_node == NULL)
        return;
    if (tree == NULL || (*tree) == NULL) {
        *tree = new_node;
        return;
    }
    tree_t *node = *tree;
    while (node != NULL) {
        if (new_node->value < node->value) {
            if (node->left == NULL) {
                node->left = new_node;
                return;
            } else {
                node = node->left;
            }
        } else if (new_node->value == node->value) {
            free(new_node);
            return;
        } else {
            if (node->right == NULL) {
                node->right = new_node;
                return;
            } else {
                node = node->right;
            }
        }
    }
}

void tree_insert(tree_t **tree, int value) {
    tree_t *new_node = (tree_t *) malloc(sizeof(tree_t));
    if (new_node == NULL) {
        return;
    }
    (new_node)->value = value;
    (new_node)->left = NULL;
    (new_node)->right = NULL;
    tree_insert_node(tree, new_node);
}

int tree_search(tree_t *tree, int value) {
    tree_t *node = tree;
    while (node != NULL) {
        if (value < node->value) {
            node = node->left;
        } else {
            if (value == node->value) {
                return 1;
            } else {
                node = node->right;
            }
        }
    }
    return 0;
}

void tree_delete(tree_t **tree, int value) {
    tree_t *node = *tree;
    tree_t *parent = node;
    int flag = 1;

    while (node != NULL) {
        if (value < node->value) {
            parent = node;
            flag = 1;
            node = node->left;
        } else {
            if (value == node->value) {
                if (node == *tree) {
                    if ((*tree)->right != NULL) {
                        node = (*tree)->left;
                        (*tree) = (*tree)->right;
                        tree_insert_node(tree, node);
                    } else {
                        (*tree) = (*tree)->left;
                    }
                    return;
                }

                if (flag) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
                tree_insert_node(tree, node->left);
                tree_insert_node(tree, node->right);
                free(node);
                return;
            } else {
                parent = node;
                flag = 0;
                node = node->right;
            }
        }
    }
}

int counting_widths(tree_t *tree) {
    if (tree == NULL) {
        return 0;
    }
    char subtree_str[10] = {0};
    sprintf(subtree_str, "%i", tree->value);
    int subtree_width = strlen(subtree_str);
    tree->width = subtree_width + counting_widths(tree->left) + counting_widths(tree->right);
    return tree->width;
}

void print_tree_help(tree_t *node, int n) {
    if (node != NULL) {
        print_tree_help(node->right, n + 1);
        for (int i = 0; i < n; i++) {
            putchar('\t');
        }
        printf("%d (%d)", node->value, node->width);
        printf("\n");
        print_tree_help(node->left, n + 1);
    }
}

void print_tree(tree_t *tree) {
    counting_widths(tree);
    print_tree_help(tree, 2);
}

int main() {
    int value;
    char key;
    tree_t *tree = NULL;
    while (scanf("%c", &key) >= 1) {
        if (key != 'p' && key != 'q') {
            scanf("%i", &value);
        }
        switch (key) {
            case 'a':
                tree_insert(&tree, value);
                break;
            case 'r':
                tree_delete(&tree, value);
                break;
            case 'f':
                if (tree_search(tree, value))
                    puts("yes");
                else
                    puts("no");
                break;
            case 'p':
                print_tree(tree);
                break;
            case 'q':
                return 0;
        }
    }
    return 0;
}