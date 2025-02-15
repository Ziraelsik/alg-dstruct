#include <stdio.h>
#include <stdlib.h>

#define compLT(a, b) (a < b)
#define compEQ(a, b) (a == b)

typedef enum {
    BLACK, RED
} node_color;

typedef struct tree_t {
    struct tree_t *left;         /* left child */
    struct tree_t *right;        /* right child */
    struct tree_t *parent;       /* parent */
    node_color color;            /* node color (BLACK, RED) */
    int data;                     /* data stored in node */
} tree_t;

#define NIL &sentinel           /* all leafs are sentinels */
tree_t sentinel = {NIL, NIL, 0, BLACK, 0};
tree_t *root = NIL;               /* root of Red-Black tree */

void rotate_left(tree_t *x) {
    /**************************
     *  rotate node x to left *
     **************************/
    tree_t *y = x->right;

    /* establish x->right link */
    x->right = y->left;
    if (y->left != NIL) y->left->parent = x;

    /* establish y->parent link */
    if (y != NIL) y->parent = x->parent;
    if (x->parent) {
        if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
    } else {
        root = y;
    }

    /* link x and y */
    y->left = x;
    if (x != NIL) x->parent = y;
}

void rotate_right(tree_t *x) {

    /****************************
     *  rotate node x to right  *
     ****************************/

    tree_t *y = x->left;

    /* establish x->left link */
    x->left = y->right;
    if (y->right != NIL) {
        y->right->parent = x;
    }

    /* establish y->parent link */
    if (y != NIL) {
        y->parent = x->parent;
    }
    if (x->parent) {
        if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
    } else {
        root = y;
    }

    /* link x and y */
    y->right = x;
    if (x != NIL) x->parent = y;
}

void insert_fix(tree_t *x) {
    /*************************************
     *  maintain Red-Black tree balance  *
     *  after inserting node x           *
     *************************************/

    /* check Red-Black properties */
    while (x != root && x->parent->color == RED) {
        /* we have a violation */
        if (x->parent == x->parent->parent->left) {
            tree_t *y = x->parent->parent->right;
            if (y->color == RED) {
                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                /* uncle is BLACK */
                if (x == x->parent->right) {
                    /* make x a left child */
                    x = x->parent;
                    rotate_left(x);
                }
                /* recolor and rotate */
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_right(x->parent->parent);
            }
        } else {
            /* mirror image of above code */
            tree_t *y = x->parent->parent->left;
            if (y->color == RED) {
                /* uncle is RED */
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                /* uncle is BLACK */
                if (x == x->parent->left) {
                    x = x->parent;
                    rotate_right(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotate_left(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

tree_t *insert_node(int data) {
    tree_t *current, *parent, *x;

    /***********************************************
     *  allocate node for data and insert in tree  *
     ***********************************************/

    /* find where node belongs */
    current = root;
    parent = 0;
    while (current != NIL) {
        if (compEQ(data, current->data)) {
            return (current);
        }
        parent = current;
        current = compLT(data, current->data) ?
                  current->left : current->right;
    }

    /* setup new node */
    if ((x = malloc(sizeof(*x))) == 0) {
        printf("insufficient memory (insertNode)\n");
        exit(1);
    }
    x->data = data;
    x->parent = parent;
    x->left = NIL;
    x->right = NIL;
    x->color = RED;

    /* insert node in tree */
    if (parent) {
        if (compLT(data, parent->data)) {
            parent->left = x;
        } else {
            parent->right = x;
        }
    } else {
        root = x;
    }

    insert_fix(x);
    return (x);
}

void delete_fix(tree_t *x) {

    /*************************************
     *  maintain Red-Black tree balance  *
     *  after deleting node x            *
     *************************************/

    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            tree_t *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_left(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotate_right(w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotate_left(x->parent);
                x = root;
            }
        } else {
            tree_t *w = x->parent->left;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                rotate_right(x->parent);
                w = x->parent->left;
            }
            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotate_left(w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotate_right(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

void delete_node(tree_t *z) {
    tree_t *x, *y;

    /*****************************
     *  delete node z from tree  *
     *****************************/

    if (!z || z == NIL) {
        return;
    }

    if (z->left == NIL || z->right == NIL) {
        /* y has a NIL node as a child */
        y = z;
    } else {
        /* find tree successor with a NIL node as a child */
        y = z->right;
        while (y->left != NIL) y = y->left;
    }

    /* x is y's only child */
    if (y->left != NIL) {
        x = y->left;
    } else {
        x = y->right;
    }

    /* remove y from the parent chain */
    x->parent = y->parent;
    if (y->parent) {
        if (y == y->parent->left) {
            y->parent->left = x;
        } else {
            y->parent->right = x;
        }
    } else {
        root = x;
    }
    if (y != z) {
        z->data = y->data;
    }


    if (y->color == BLACK) {
        delete_fix(x);
    }
    free(y);
}

tree_t *find_node(int data) {
    /*******************************
     *  find node containing data  *
     *******************************/
    tree_t *current = root;
    while (current != NIL) {
        if (compEQ(data, current->data)) {
            return (current);
        } else {
            current = compLT (data, current->data) ?
                      current->left : current->right;
        }
    }
    return NULL;
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
                insert_node(value);
                break;
            case 'r':
                tree = find_node(value);
                delete_node(tree);
                break;
            case 'f':
                if (find_node(value))
                    puts("yes");
                else
                    puts("no");
                break;
            case 'q':
                return 0;
        }
    }
    return 0;
}