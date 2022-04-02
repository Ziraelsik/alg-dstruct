#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *parent;
    struct node *sons[4];
    int length;
    int keys[3];
} node;

node *root = NULL;


typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
    node *val;
} list_node;


list_node *list_add(list_node *l, node *v) {
    list_node *n = (list_node *) malloc(sizeof(list_node));
    l->next = n;
    n->next = NULL;
    n->prev = l;
    n->val = v;
    return n;
}

typedef struct split_retval {
    node *left;
    node *right;
} split_retval;


node *Node() {
    node *n = (node *) malloc(sizeof(node));
    n->parent = NULL;
    n->length = 1;
    n->sons[0] = NULL;
    n->sons[1] = NULL;
    n->sons[2] = NULL;
    n->sons[3] = NULL;
    return n;
}


node *search(node *v, int x) {
    node *t = v;

    if (t == NULL) {
        return NULL;
    }
    while (t->length != 1) {
        if (t->length == 2) {
            if (x <= t->keys[0]) {
                t = t->sons[0];
            } else {
                t = t->sons[1];
            }
        } else if (x <= t->keys[0]) {
            t = t->sons[0];
        } else if (x <= t->keys[1]) {
            t = t->sons[1];
        } else {
            t = t->sons[2];
        }
    }
    return t;
}


int cmpfu(const void *a, const void *b) {
    node **val1 = (node **) a;
    node **val2 = (node **) b;

    return (*val1)->keys[0] - (*val2)->keys[0];
}

void sort_son(node *v) {
    if (v == NULL) {
        return;
    }
    node *arr[4];
    for (int i = 0; i < v->length; i++) {
        arr[i] = v->sons[i];
    }
    qsort(arr, v->length, sizeof(node *), cmpfu);

    for (int i = 0; i < v->length; i++) {
        v->sons[i] = arr[i];
    }
}


int subtree_max(node *v) {
    node *t = v;
    while (t->length != 1) {
        t = t->sons[t->length - 1];
    }
    return t->keys[0];
}


void update_keys(node *v) {
    if (v == NULL) {
        return;
    }

    node *p = v->parent;
    while (p != NULL) {
        for (int i = 0; i < p->length - 1; i++) {
            p->keys[i] = subtree_max(p->sons[i]);
        }
        p = p->parent;
    }
}


void split_parent(node *t) {
    if (t == NULL) return;
    if (t->length > 3) {
        node *b = Node();
        b->parent = t->parent;
        b->sons[0] = t->sons[2];
        b->sons[1] = t->sons[3];
        b->keys[0] = t->keys[2];
        b->length = 2;
        t->sons[2]->parent = b;
        t->sons[3]->parent = b;
        t->length = 2;
        t->sons[2] = NULL;
        t->sons[3] = NULL;

        node *p = t->parent;
        if (p != NULL) {
            p->sons[p->length] = b;
            b->parent = p;
            p->length++;
            sort_son(p);
            update_keys(b);
            split_parent(p);
        } else {
            node *new_root = Node();
            new_root->sons[0] = t;
            new_root->sons[1] = b;
            new_root->keys[0] = t->keys[1];
            new_root->length = 2;
            t->parent = new_root;
            b->parent = new_root;
            root = new_root;
        }
    }
}

node *add(node *t, int x) {
    node *n = (node *) malloc(sizeof(node));
    n->length = 1;
    n->keys[0] = x;
    t = root;

    if (t == NULL) {
        root = n;
        return root;
    }
    node *a = search(t, x);
    if (a->keys[0] == x) return root;
    if (a->parent == NULL) {
        node *new_root = Node();
        new_root->length = 2;
        new_root->sons[0] = a;
        new_root->sons[1] = n;
        a->parent = new_root;
        n->parent = new_root;
        sort_son(new_root);
        root = new_root;
    } else {
        node *p = a->parent;
        p->sons[p->length] = n;
        n->parent = p;
        p->length++;
        sort_son(p);
        update_keys(n);
        split_parent(p);
    }
    update_keys(n);

    return root;
}

node *find_brother(node *v) {
    node *p = v->parent;
    if (p == NULL) {
        return NULL;
    }
    if (p->length == 1) {
        return NULL;
    }

    int pos;
    for (int i = 0; i < p->length; i++) {
        if (v == p->sons[i]) {
            pos = i;
            break;
        }
    }

    if (pos == 0 || pos == 2) {
        return p->sons[1];
    } else {
        return p->sons[0];
    }
}

void delete_in_node(node *v) {
    node *p = v->parent;
    int pos = 4;

    for (int i = 0; i < p->length; i++) {
        if (v == p->sons[i]) {
            pos = i;
            free(p->sons[i]);
        }
        if (i > pos) {
            p->sons[i - 1] = p->sons[i];
        }
    }
    p->length--;
    update_keys(p->sons[0]);
}

node *del(node *v, int x) {
    node *t = search(v, x);
    if (t == NULL) {
        return NULL;
    }

    if (t->keys[0] != x) return root;

    node *p = t->parent;

    if (p == NULL) {
        free(v);
        root = NULL;
    } else {
        if (p->length > 2) {
            delete_in_node(t);
            return root;
        }
        if (p->length == 2) {
            node *np = find_brother(p);
            if (np == NULL) {
                delete_in_node(t);
                p->sons[0]->parent = NULL;
                root = p->sons[0];
            } else {
                node *b = find_brother(t);
                np->sons[np->length] = b;
                b->parent = np;
                np->length++;
                p->length = 1;
                p->keys[0] = x;
                sort_son(np);
                del(v, x);
                update_keys(b);
                split_parent(np);
                update_keys(b);
            }
        }
    }
    return root;
}

int get_height(node *v) {
    int h = 0;
    while (v->length != 1) {
        h++;
        v = v->sons[0];
    }
    return h;
}


node *merge(node *l, node *r) {
    if (l == NULL) {
        return r;
    }
    if (r == NULL) {
        return l;
    }
    int h_right = get_height(r);
    int h_left = get_height(l);
    if (h_left == h_right) {
        node *new_root = (node *) malloc(sizeof(node));
        new_root->length = 2;
        new_root->sons[0] = l;
        l->parent = new_root;
        new_root->sons[1] = r;
        r->parent = new_root;
        update_keys(r);
        return new_root;
    }

    node *v;
    if (h_right > h_left) {
        v = r;
        while (abs(h_right - get_height(v)) > 1) {
            v = v->sons[0];
        }
        r->sons[r->length] = l;
        r->length++;
        l->parent = r;
        sort_son(r);
        update_keys(l);
        node *new_root = r;
        split_parent(r);
        return new_root;
    } else {
        v = l;
        while (abs(h_left - get_height(v)) > 1) {
            v = v->sons[0];
        }
        l->sons[l->length] = r;
        l->length++;
        r->parent = l;
        update_keys(r);
        node *new_root = l;
        split_parent(l);
        return new_root;
    }

}


split_retval split(node *t, int key) {
    list_node *l_list = (list_node *) malloc(sizeof(list_node));
    list_node *l_ptr = l_list;
    list_node *r_list = (list_node *) malloc(sizeof(list_node));
    list_node *r_ptr = r_list;

    while (t->length != 1) {
        if (t->length == 2) {
            if (key <= t->keys[0]) {
                r_ptr = list_add(r_ptr, t->sons[1]);
                t = t->sons[0];
            } else {
                l_ptr = list_add(l_ptr, t->sons[0]);
                t = t->sons[1];
            }
        } else if (key <= t->keys[0]) {
            r_ptr = list_add(r_ptr, t->sons[1]);
            r_ptr = list_add(r_ptr, t->sons[2]);
            t = t->sons[0];
        } else if (key <= t->keys[1]) {
            l_ptr = list_add(l_ptr, t->sons[0]);
            r_ptr = list_add(r_ptr, t->sons[2]);
            t = t->sons[1];
        } else {
            l_ptr = list_add(l_ptr, t->sons[0]);
            l_ptr = list_add(l_ptr, t->sons[1]);
            t = t->sons[2];
        }
    }
    l_ptr = list_add(l_ptr, t);

    node *l = NULL;
    node *r = NULL;
    l_ptr = l_list->next;
    while (l_ptr != NULL) {
        l = merge(l, l_ptr->val);
        l_ptr = l_ptr->next;
    }
    while (r_ptr != r_list) {
        r = merge(r, r_ptr->val);
        r_ptr = r_ptr->prev;
    }

    split_retval ret;
    ret.left = l;
    ret.right = r;
    return ret;
}


int main() {
    char cmd;
    int key;
    node *tree = NULL;

    while (fscanf(stdin, "%c %d", &cmd, &key) > 0) {
        if (cmd == 'a') {
            tree = add(tree, key);
        }

        if (cmd == 'r') {
            tree = del(tree, key);
        }
        if (cmd == 'f') {
            node *s = search(tree, key);
            if (s != NULL) {
                if (s->keys[0] == key) {
                    printf("yes\n");
                } else {
                    printf("no\n");
                }
            } else {
                printf("no\n");
            }
        }
    }

    return 0;
}
