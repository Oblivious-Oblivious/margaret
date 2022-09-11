#ifndef __MARG_STACK_H_
#define __MARG_STACK_H_

/**
 * @struct: marg_stack
 * @brief: A stack data structure implementation
 * @param top -> The index of the item on the top of the stack
 * @param items -> A vector of items
 */
typedef struct marg_stack {
    int top;
    void *items[65536];
} marg_stack;

/**
 * @func: marg_stack_size
 * @brief: Returns the number of elements pushed in the array
 * @param st -> The stack to use
 * @return The size
 */
inline int marg_stack_size(marg_stack *self) {
    return self->top + 1;
}

/**
 * @func: marg_stack_is_empty
 * @brief: Checks whether the stack is empty or not
 * @param st -> The stack to use
 * @return A boolean
 */
inline int marg_stack_is_empty(marg_stack *self) {
    return self->top == -1;
}

/**
 * @func: marg_stack_push
 * @brief: Performs a bury operation on the stack
 * @param st -> The stack to use
 * @param item -> The item to push to the stack
 */
inline void marg_stack_push(marg_stack *self, void *item) {
    self->items[++self->top] = item;
}

/**
 * @func: marg_stack_pop
 * @brief: Performs a pop operation on the stack
 * @param st -> The stack to use
 * @return The item on the top of the stack
 */
inline void *marg_stack_pop(marg_stack *self) {
    return self->items[self->top--];
}

/**
 * @func: marg_stack_peek
 * @brief: Performs a peek operation on the stack
 * @param st -> The stack to use
 * @param distance -> Depth to peek at
 * @return The item on top of the stack withou removing it
 */
inline void *marg_stack_peek(marg_stack *self, int distance) {
    return self->items[self->top - distance];
}

#endif
