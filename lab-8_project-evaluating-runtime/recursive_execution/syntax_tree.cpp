#include "global.h"
#include <iostream>
#include "../timer.cpp"

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
            case ' ':
                break;
            case NUM:
                return p->leaf_value;
            case ID:
                if (symtable[p->leaf_value].value_initialized){
                    return symtable[p->leaf_value].value;
                }
                else
                    printf("Error: variable %s not initialized!", symtable[p->leaf_value].lexeme);
                break;
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
                break;
            }
            case '?':
                return execute(p->args[0]) ? execute(p->args[1]) : execute(p->args[2]);
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

void execute_recursively(TreeNode *p) {
    timer stopwatch;
    stopwatch.start();
    execute(p);
    stopwatch.stop();
    exit(0);
}
