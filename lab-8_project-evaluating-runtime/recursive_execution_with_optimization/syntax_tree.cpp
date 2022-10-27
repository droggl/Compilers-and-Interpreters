#include "global.h"
#include <iostream>
#include "../timer.cpp"


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

TreeNode* cpnode(TreeNode* p) {
    TreeNode* new_node = new TreeNode();
    new_node->type = p->type;
    new_node->leaf_value = p->leaf_value;
    new_node->args[0] = p->args[0];
    new_node->args[1] = p->args[1];
    new_node->args[2] = p->args[2];
    new_node->args[3] = p->args[3];
    return new_node;
}

TreeNode* optimize(TreeNode* p) {
    if (p == 0)
        return 0;

    switch (p->type) {
        case NUM:
        case ID:
            return cpnode(p);
        case '+': case '-':
            if (p->args[0]->type == NUM && p->args[0]->leaf_value == 0) {
                return cpnode(p->args[1]);
            } else if (p->args[1]->type == NUM && p->args[1]->leaf_value == 0) {
                return cpnode(p->args[0]);
            } else if (p->args[0]->type == NUM && p->args[1]->type == NUM) {
                return mkleaf(NUM, execute(p));
            }
            break;
        case '*':
            if (p->args[0]->type == NUM && p->args[0]->leaf_value == 1) {
                return cpnode(p->args[1]);
            } if (p->args[1]->type == NUM && p->args[1]->leaf_value == 1) {
                return cpnode(p->args[0]);
            } else if (p->args[0]->type == NUM && p->args[1]->type == NUM) {
                return mkleaf(NUM, execute(p));
            }
            break;
        case '/':
            if (p->args[1]->type == NUM && p->args[1]->leaf_value == 1) {
                return cpnode(p->args[0]);
            } else if (p->args[0]->type == NUM && p->args[1]->type == NUM) {
                return mkleaf(NUM, execute(p));
            }
            break;
        case '%':
            if (p->args[1]->type == NUM && p->args[1]->leaf_value == 1) {
                return mkleaf(NUM, 0);
            } else if (p->args[0]->type == NUM && p->args[1]->type == NUM) {
                return mkleaf(NUM, execute(p));
            }
            break;
        case '?':
        case IF:
        {
            TreeNode* cond = p->args[0];
            if (cond->args[0]->type == NUM && cond->args[1]->type == NUM) {
                int condition = execute(cond->args[0]);
                if (condition)
                    return cpnode(p->args[1]);
                else
                    return cpnode(p->args[2]);
            }
            break;
        }

    }
    TreeNode* new_node = new TreeNode();
    new_node->type = p->type;
    for (int i=0; i<4; i++) {
        new_node->args[i] = optimize(p->args[i]);
    }
    return new_node;

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
    TreeNode* opt_p1 = optimize(p);
    TreeNode* opt_p2 = optimize(opt_p1);
    TreeNode* opt_p3 = optimize(opt_p2);

    timer stopwatch;
    stopwatch.start();
    execute(opt_p3);
    stopwatch.stop();
    exit(0);
}

