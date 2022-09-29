// # --- Topics --- #
// Syntax trees and how to construct them

E -> id | E + E

x+y

  E
 /|\
E | E       +
| | |  =>  / \
x + y     x   y

Parse     Syntax
 tree      tree



// Construction of syntax trees
E -> E1 + T | E1 - T | T
T -> ( E ) | id | num

#define MAX_ARGS 4

enum TreeNodeType { IF, WHILE, PLUS, MINUS, TIMES };

struct TreeNode {
  enum TreeNodeType type;
  struct TreeNode* args[MAX_ARGS];
};


Production          |   Semantic rule
--------------------|-------------------------
E1 -> E2 + T        |   E1.nodeptr = mknode(PLUS, E2.nodeptr, T.nodeptr, NULL);
E1 -> E2 - T        |   E1.nodeptr = mknode(MINUS, E2.nodeptr, T.nodeptr, NULL);
E -> T              |   E.nodeptr = T.nodeptr
T -> (E)            |   T.nodeptr = E.nodeptr
T -> id             |   T.nodeptr = mkleaf(ID, id.lexicalval)
T -> num            |   T.nodeptr = mkleaf(NUM, num.lexicalval)


