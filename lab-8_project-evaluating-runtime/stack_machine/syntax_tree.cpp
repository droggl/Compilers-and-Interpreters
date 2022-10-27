#include <iostream>
#include <stdio.h>
#include "global.h"
#include "StackMachine.h"
#include "../timer.cpp"

void push_to_stack(TreeNode* p);
int execute(TreeNode* p);
void execute_in_stack_machine(TreeNode* p);
extern int nr_symbols;

#define MAX_ARGS 4

StackMachine sm;
int lowest_label = 1;

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

void push_to_stack(TreeNode* p) {
    if (p == 0)
        return;

    switch (p->type) {
        case ';':
            push_to_stack(p->args[0]);
            push_to_stack(p->args[1]);
            return;
        case ' ':
            return;
        case NUM:
            // print("%d", p->leaf_value);
            sm.append(Instruction(push, p->leaf_value));
            return;
        case ID:
            // print("%s", symtable[p->leaf_value].lexeme);
            sm.append(Instruction(rvalue, p->leaf_value));
            return;
        case '=':
            sm.append(Instruction(lvalue, p->args[0]->leaf_value));
            // print("%s", symtable[p->args[0]->leaf_value].lexeme);
            push_to_stack(p->args[1]);

            sm.append(Instruction(assign));
            // print("%c", p->type);
            return;
        case READ:
        {
            sm.append(Instruction(lvalue, p->args[0]->leaf_value));
            sm.append(Instruction(stackop_read));
            sm.append(Instruction(assign));
            return;
        }
        case PRINT:
            sm.append(Instruction(rvalue, p->args[0]->leaf_value));
            sm.append(Instruction(stackop_write));
            return;
        case '?':
        case IF:
        {
            int label1 = lowest_label;
            int label2 = lowest_label+1;
            lowest_label+=2;
            push_to_stack(p->args[0]);                          // push condition
            sm.append(Instruction(gofalse, label1));      // jumpfalse to label 1
            push_to_stack(p->args[1]);                          // push if part
            sm.append(Instruction(jump, label2));       // jump to label 2 over else part
            sm.append(Instruction(label, label1));        // label 1
            push_to_stack(p->args[2]);                          // push else part
            sm.append(Instruction(label, label2));      // label 2
            return;
        }
        case WHILE:
        {
            int label1 = lowest_label;
            int label2 = lowest_label+1;
            lowest_label+=2;
            sm.append(Instruction(label, label1));        // label 1
            push_to_stack(p->args[0]);                          // push condition
            sm.append(Instruction(gofalse, label2));    // jumpfalse to label 2
            push_to_stack(p->args[1]);                          // push statement part
            sm.append(Instruction(jump, label1));         // jump to label 1
            sm.append(Instruction(label, label2));      // label 2
            lowest_label++;
            return;
        }
    }

    push_to_stack(p->args[0]);
    push_to_stack(p->args[1]);
    push_to_stack(p->args[2]);
    push_to_stack(p->args[3]);
    // print("%c", p->type);
    switch (p->type) {
        case '+':
            sm.append(Instruction(plus));
            break;
        case '-':
            sm.append(Instruction(minus));
            break;
        case '*':
            sm.append(Instruction(times));
            break;
        case '/':
            sm.append(Instruction(divide));
            break;
        case '%':
            sm.append(Instruction(modulo));
            break;
        case '&':
            sm.append(Instruction(stackop_and));
            break;
        case '|':
            sm.append(Instruction(stackop_or));
            break;
        case '<':
            sm.append(Instruction(lt));
            break;
        case '>':
            sm.append(Instruction(gt));
            break;
    }

}

void execute_in_stack_machine(TreeNode* p) {
    push_to_stack(p);
    sm.append(Instruction(halt));
    timer stopwatch;
    stopwatch.start();
    sm.run();
    stopwatch.stop();
    exit(0);
}


int execute(TreeNode* p) {
    if (p != 0) {
        switch (p->type) {
            case ' ':
                break;
            case NUM:
                return p->leaf_value;
            case ID:
                if (symtable[p->leaf_value].value != -1){
                    return symtable[p->leaf_value].value;
                }
                else
                    // print("Error: variable %s not initialized!", symtable[p->leaf_value].lexeme);
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
                // print("%d\n", execute(p->args[0]));
                break;
            case READ:
            {
                int n;
                std::cin >> n;
                symtable[p->args[0]->leaf_value].value = n;
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
