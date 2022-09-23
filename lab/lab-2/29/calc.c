/* calc.c */

#include "global.h"

int top = -1; /* top of stack */
int stack[N];

void calc(int token_type, int token_value), push(int t);
int pop();

int assignment_token_id;

void calc (int token_type, int token_value)  /* calculates expressions */
{
    int x;
    switch(token_type) {
    case '+' :
        x = pop() + pop(); push(x); break;
    case '-' :
    {
        int a, b;
        a = pop(); b = pop(); x = b - a; 
        push(x); break;
    }
    case '*' :
        x = pop() * pop(); push(x); break;
    case '/':
    {
        int a, b;
        a = pop(); b = pop(); x = b / a; 
        push(x);
        break;
    }
    case '^':
    {
        int i, a, b;
        a = pop(); b = pop(); x = 1;
        for (i=0; i<a; i++) {
            x *= b;
        }
        push(x); break;
    }
    case '=':
    {
        int token_id;
        // pop expression value;
        x = pop();
        printf("%d\n", x);

        // pop variable symtable id;
        token_id = pop();

        symtable[token_id].value = x;
        symtable[token_id].value_initialized = true;
        break;
    }
    case NUM:
        push(token_value); break;
    case ID:
    {
        if (top == -1) {
            // for first variable push id into stack
            push(token_value);
        } else {
            // for all other variables check if value is initialized else error()
            if (symtable[token_value].value_initialized) {
                // push value of id onto stack;
                push(symtable[token_value].value); 
            } else {
                error("Variable not initialized.");
            }
        }
        break;

    }
    default:     
        printf("[Unknown token %d, with value %d]\n", token_type, token_value);
    }
}

void push(int t) {
    if (top == N-1) {
        error("Stack overflow");
    } else {
        top += 1;
        stack[top] = t;
    }
}

int pop(){
    if(top == -1)
        printf("Underflow State: Stack already empty, can't remove any element\n");
    else{
        int x = stack[top];
        top-=1;
        return x;
    }
    return -1;
}
