#include "memallocator.h"

#define FREE 1
#define NOT_FREE 0

typedef struct node {
    struct node *next;
    struct node *prev;
    int status;
    int size;
} node_t;

typedef struct descriptor {
    node_t *head;
    int full_size;
} descriptor_t;

descriptor_t descriptor = {nullptr, 0};

int meminit(void *ptr, int size) {
    if (ptr == nullptr) {
        return 1;
    }
    int min_size = memgetminimumsize();
    int block_size = memgetblocksize();
    if (size < min_size) {
        return 1;
    }
    descriptor.head = (node_t *) ptr;
    descriptor.head->status = FREE;
    descriptor.head->next = nullptr;
    descriptor.head->prev = nullptr;
    descriptor.head->size = size - block_size;
    descriptor.full_size = size;
    return 0;

}

void *memalloc(int size) {
    int block_size = memgetblocksize();
    node_t *best_fit_ptr = nullptr;

    void *ptr = nullptr;
    if ((size <= 0) || (descriptor.head == nullptr)) {
        return ptr;
    }
    node_t *header = descriptor.head;
    while (header != nullptr) {
        if ((header->size >= size) && (header->status == FREE)) {
            if ((best_fit_ptr == nullptr) || (header->size < best_fit_ptr->size)) {
                best_fit_ptr = header;
            }
        }
        header = header->next;
    }
    if (best_fit_ptr == nullptr) {
        return ptr;
    }
    if (best_fit_ptr->size <= size + memgetminimumsize()) {
        best_fit_ptr->status = NOT_FREE;
        ptr = (void *) ((char *) best_fit_ptr + block_size);
        return ptr;
    }
    node_t *node;
    node = (node_t *) ((char *) best_fit_ptr + size + block_size);
    node->prev = best_fit_ptr;
    node->next = best_fit_ptr->next;
    if (best_fit_ptr->next != nullptr) {
        best_fit_ptr->next->prev = node;
    }
    best_fit_ptr->next = node;
    best_fit_ptr->status = NOT_FREE;
    node->status = FREE;
    node->size = best_fit_ptr->size - size - block_size;
    best_fit_ptr->size = size;
    ptr = (void *) ((char *) best_fit_ptr + block_size);
    return ptr;
}

void memfree(void *ptr) {
    if ((ptr == nullptr) && (descriptor.head == nullptr)) {
        return;
    }
    int block_size = memgetblocksize();
    node_t *temp_ptr;
    node_t *first_free_ptr;
    first_free_ptr = (node_t *) ((char *) ptr - block_size);

    if ((first_free_ptr < descriptor.head) && (first_free_ptr > (descriptor.head + descriptor.full_size))) {
        return;
    }
    first_free_ptr->status = FREE;

    if (first_free_ptr->next != nullptr) {
        if (first_free_ptr->next->status == FREE) {
            temp_ptr = first_free_ptr;
            temp_ptr->size = temp_ptr->size + temp_ptr->next->size + block_size;
            if (temp_ptr->next->next != nullptr) {
                temp_ptr->next->next->prev = temp_ptr;
                temp_ptr->next = temp_ptr->next->next;
            } else {
                temp_ptr->next = nullptr;
            }
        }
    }

    if (first_free_ptr->prev != nullptr) {
        if (first_free_ptr->prev->status == FREE) {
            temp_ptr = first_free_ptr->prev;
            if (temp_ptr->next != nullptr) {
                temp_ptr->size = temp_ptr->size + temp_ptr->next->size + block_size;
            }
            if (temp_ptr->next->next != nullptr) {
                temp_ptr->next->next->prev = temp_ptr;
                temp_ptr->next = temp_ptr->next->next;
            } else {
                temp_ptr->next = nullptr;
            }
        }
    }
}

void memdone() {
    descriptor.head = nullptr;
    descriptor.full_size = 0;
}

int memgetminimumsize() {
    return sizeof(node_t);
}

int memgetblocksize() {
    return sizeof(node_t);
}
