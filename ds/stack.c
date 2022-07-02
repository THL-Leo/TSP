#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
struct Stack {
    uint32_t top;
    uint32_t capacity;
    uint32_t *items;
};

Stack *stack_create(uint32_t capacity) { // initialize stack using code from Dr. Long
    Stack *s = (Stack *) malloc(sizeof(Stack));
    if (s) {
        s->top = 0;
        s->capacity = capacity;
        s->items = (uint32_t *) calloc(capacity, sizeof(uint32_t));
        if (!s->items) {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void stack_delete(Stack **s) { // delete the stack
    if (*s && (*s)->items) {
        free((*s)->items); // free the array too
        free(*s);
        *s = NULL; // setting the pointer to null so no one calls it
    }
    return;
}

uint32_t stack_size(Stack *s) { // top is the size of the stack
    return s->top;
}

bool stack_empty(Stack *s) { // check if top is 0
    return (s->top == 0);
}

bool stack_full(Stack *s) { // check if top is equal to capacity
    return (s->top == s->capacity);
}

bool stack_push(Stack *s, uint32_t x) { // push x into the stack
    if (!stack_full(s)) {
        s->items[s->top] = x;
        s->top++; // increment the index
        return true;
    }
    return false;
}

bool stack_pop(Stack *s, uint32_t *x) { // pop form the stack
    if (!stack_empty(s)) {
        s->top--; // decrement
        *x = s->items[s->top]; // pop it out
        return true;
    }
    return false;
}

bool stack_peek(Stack *s, uint32_t *x) {
    if (!stack_empty(s)) {
        *x = s->items[s->top - 1]; // peek without decrementing top
        return true;
    }
    return false;
}

void stack_copy(Stack *dst, Stack *src) {
    free(dst->items); // free the array first
    dst->items = (uint32_t *) calloc(
        src->capacity, sizeof(uint32_t)); // allocate space if size is different
    for (uint32_t i = 0; i < src->top; i++) {
        dst->items[i] = src->items[i];
    }
    dst->top = src->top; // setting everything to the src
    dst->capacity = src->capacity;
}

void stack_print(Stack *s, FILE *outfile, char *cities[]) {
    for (uint32_t i = 0; i < s->top; i++) { // priting cities in the way the program wants it
        fprintf(outfile, "%s", cities[s->items[i]]);
        if (i + 1 != s->top) {
            fprintf(outfile, " -> ");
        }
    }
    fprintf(outfile, "\n");
}
