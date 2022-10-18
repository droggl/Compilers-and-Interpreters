// # --- Topics --- #
// Interpreters 
//  - executing the syntax tree (lab 6)
//  - stack machines (lab 7)

int PLUS = 1;
int TIMES = 2;
int NUMBER, VAR;
int* symtable;


struct Node {
    int type;
    struct Node *args[3];
    int leaf_value;
};

int execute(struct Node *p) {
    if (p->type == PLUS) {
        return execute(p->args[0]) + execute(p->args[1]);
    }
    else if (p-> type == TIMES) {
        return execute(p->args[0]) + execute(p->args[1]);
    }
    else if (p-> type == NUMBER) {
        return p->leaf_value;
    }
    else if (p-> type == VAR) {
        return symtable[p->leaf_value].value;
    }
    else if (p->type == IF) {
        int condition = execute(p->args[0]);
        if (condition) {
            execute(p->args[1]);
        else
            execute(p->args[2]);
    }
    else if (p->type[0] == WHILE) {
        while (execute(p->args[0]))
            execute(p->args[1]);        
    }
}


if ( a > 2 ) {
    while ( a < 10 ) {
        a = a + 1;
    }
}
