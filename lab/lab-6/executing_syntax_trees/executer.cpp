#include "global.h"
#include <iostream>


extern void print_syntax_tree(TreeNode* n);
extern void printtree1(TreeNode* p, int level);
extern int execute(TreeNode* p);

#define MAX_ARGS 4

struct TreeNode {
    int type;
    int leaf_value;
    TreeNode* args[MAX_ARGS];
};

TreeNode* mkleaf(int type, int value) {
  TreeNode* p = new TreeNode();
  p->type = type;
  p->leaf_value = value;
  return p;
}

TreeNode* mknode(int type, TreeNode* a0=0, TreeNode* a1=0, TreeNode* a2=0, TreeNode* a3=0) {
  TreeNode* p = new TreeNode();
  p->type = type;
  p->args[0] = a0;
  p->args[1] = a1;
  p->args[2] = a2;
  p->args[3] = a3;
  return p;
}


int execute(TreeNode* p) {
    if (p != 0) {
        switch (p->type) {
            case NUM:
                return p->leaf_value;
            case ID:
                // printf("CHECKING ID for %d\n", p->leaf_value);
                if (symtable[p->leaf_value].value_initialized){
                    // printf("ERROR FOLLOWING?\n");
                    return symtable[p->leaf_value].value;
                }
                else
                    printf("Variable not initialized!");
                break;
                    /* return p->leaf_value; */
            case '+':
                return execute(p->args[0]) + execute(p->args[1]);
            case '-':
                return execute(p->args[0]) - execute(p->args[1]);
            case '*':
                return execute(p->args[0]) * execute(p->args[1]);
            case '/':
                return execute(p->args[0]) / execute(p->args[1]);
            case '%':
                return execute(p->args[0]) % execute(p->args[1]);
            case '^':
                return pow(execute(p->args[0]), execute(p->args[1]));
            case '&':
                return execute(p->args[0]) & execute(p->args[1]);
            case '|':
                return execute(p->args[0]) | execute(p->args[1]);
            case '<':
                return execute(p->args[0]) < execute(p->args[1]);
            case '>':
                return execute(p->args[0]) > execute(p->args[1]);
            case '=':
            {
                symtable[p->args[0]->leaf_value].value = execute(p->args[1]);
                symtable[p->args[0]->leaf_value].value_initialized = true;
                // printf("new value  %d for lexeme %s\n", p->args[0]->leaf_value, symtable[p->args[0]->leaf_value].lexeme);
                break;
            }
            case IF:
            {
                int condition = execute(p->args[0]);
                if (condition)
                    execute(p->args[1]);
                else
                    execute(p->args[2]);
                break;
            }
            case WHILE:
                while (execute(p->args[0]))
                    execute(p->args[1]);
                break;
            case PRINT:
                printf("%d\n", execute(p->args[0]));
                break;
            case READ:
            {
                int n;
                std::cin >> n;
                symtable[p->args[0]->leaf_value].value = n;
                symtable[p->args[0]->leaf_value].value_initialized = true;
                break;
            }
            case ';':
                execute(p->args[0]);
                if (p->args[1] != 0)
                    execute(p->args[1]);
                break;
        }
    }
    return 0;
}


void print_syntax_tree(TreeNode* p) {
  printf("\nSyntax tree:\n");
  printtree1(p, 0);
}

void printtree1(TreeNode* p, int level) {
    if (p==0)
        return;
    printf("%*s", level, "");
    switch (p->type) {
        case ' ':
            printf("{}\n");
            break;
        case ID:
            printf("%s\n", symtable[p->leaf_value].lexeme);
            break;
        case NUM:
            printf("%d\n", p->leaf_value);
            break;
        case '=':
            printf("=\n");
            printtree1(p->args[0], level + 4);
            printtree1(p->args[1], level + 4);
            break;
        case IF:
            printf("if\n");
            printtree1(p->args[0], level + 4);
            printtree1(p->args[1], level + 4);
            printtree1(p->args[2], level + 4);
            break;
        case WHILE:
            printf("while\n");
            printtree1(p->args[0], level + 4);
            printtree1(p->args[1], level + 4);
            break;
        case PRINT:
            printf("print\n");
            printtree1(p->args[0], level + 4);
            break;
        case READ:
            printf("read\n");
            printtree1(p->args[0], level + 4);
            break;
        case '+':  case '-': case '*': case '/': case '%': case '^': case '&': case '|': case '<': case '>':
            printf("%c\n", p->type);
            printtree1(p->args[0], level + 4);
            printtree1(p->args[1], level + 4);
            break;
        case '?':
            printf("%c\n", p->type);
            printtree1(p->args[0], level + 4);
            printtree1(p->args[1], level + 4);
            printtree1(p->args[2], level + 4);
            break;
        case ';':
            printf(";\n");
            printtree1(p->args[0], level + 4);
            if (p->args[1] != 0) {
                printtree1(p->args[1], level + 4);
            }
            break;
    }
}