#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

// Δομή για την αναπαράσταση της στοίβας
typedef struct {
    int top;
    int items[MAX_SIZE];
} Stack;

// Επιστρέφει μια καινούργια στοίβα
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

// Επιστρέφει εάν η στοίβα είναι άδεια
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Επιστρέφει το στοιχείο στην κορυφή της στοίβας
int peek(Stack* stack) {
    return stack->items[stack->top];
}

// Αφαιρεί και επιστρέφει το στοιχείο στην κορυφή της στοίβας
int pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top--];
    }
    return -1;
}

// Προσθέτει ένα στοιχείο στην κορυφή της στοίβας
void push(Stack* stack, int value) {
    stack->items[++stack->top] = value;
}

// Εκτελεί την αποτίμηση της ενθεματικής παράστασης expr
int evaluate(char* expr) {
    Stack* stack = createStack();

    for (int i = 0; expr[i] != '\0'; i++) {
        if (isdigit(expr[i])) {
            push(stack, expr[i] - '0');
        } else {
            int operand2 = pop(stack);
            int operand1 = pop(stack);
            switch (expr[i]) {
                case '+':
                    push(stack, operand1 + operand2);
                    break;
                case '-':
                    push(stack, operand1 - operand2);
                    break;
                case '*':
                    push(stack, operand1 * operand2);
                    break;
                case '/':
                    push(stack, operand1 / operand2);
                    break;
            }
        }
    }

    int result = pop(stack);
    free(stack);
    return result;
}

int main() {
    char expression[] = "42*3+";
    printf("Result: %d\n", evaluate(expression));
    return 0;
}
