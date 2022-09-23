// # --- The Parser --- #
// Predictive recursive-descent parser
// one function for each non-terminal

// Grammar:
type -> simple
simple -> integer
simple -> char
simple -> num dotdot num
type -> array [ simple ] of type
type -> ^type

source program:
       num   num
array [ 1 .. 10 ] of integer;
^
|
lookahead token
= current token

// Assume:
scan()

lookahead = scan();

void match(int expected) {
    if (lookahead != expected)
        error();
    lookahead = scan();
}

void simple() {
    if (lookahead == integer) {
        match(integer);
    }
    else if (lookahead == char) {
        match(char);
    }
    else if (lookahead == num) {
        match(num); match(dotdot); match(num);
    }
    else
        error();
}

void type() {
    if (lookahead == integer or 
        lookahead == char or 
        lookahead == num) {
            simple();
    }    
    else if (lookahead == array) {
        match(array); match([); simple(); match(]); match(of); type();        
    }
    else if (lookahead == ^) {
        match(^); type();
    }
    else {
        error();
    }
}


// # --- FIRST() conflicts --- #
A -> xy | xz
FIRST(xy) = {x}
FIRST(xz) = {x}
input: x...


command -> eld | eld uphör 
OR
command -> eld
command -> eld uphör

// not working version:
void command() {
    if (lookahead == eld ) {
        match(eld);
    }
    else if (lookahead == eld) {
        match(eld); match(upphör)
    }
}

// to solve the problem: left factoring
command -> eld rest
rest -> upphör | symbol(element)

left factoring: xy + xz -> x(y+z)
eld upphör



// # --- Left Recursion --- #

expr -> number | expr + number

Problem: expr -> expr + number
           ^      ^
           |      |
           left recursion

void expr() {
    if (lookahead == number) {
        expr(); match(+); match(number);
    }
    ...
}

Ex input: 2 + 3 + 4
          ^
          |
        lookahead

    => jump from expr in expr in expr ...

Transform the grammar to remove the left recursion!
A -> A x | y
    |
    v
A -> y Rest
Rest -> x Rest | symbol(element)

// Code
void expr() {
    match(y); Rest();
}

void Rest() {
    if (lookahead == x) {
        match(x); Rest();
    }
    else {
        // ok!
    }
}



// # --- How to write a top-town parser --- #
1. Decide the language
2. Write a grammar for that language
3. Remove ambiguity
------------------------------------------------------------------
4. Remove FIRST() conflicts (by left factoring) |  OR: use a tool like Bison
5. Remove Left Recursion                        |
6. Write the parser                             |



// # --- The "2.5" program --- #
Language:   2 => 2
            2+3 => 23+
            2+3+4-5-6 => 23+4+5-6-
    not:    2*3
            12+3
            6-(5-4)
            6-++
            6/7

// simple grammar
expr -> term | expr + term| expr - term
term -> 0|1|2|3|4|5|6|7|8|9

// grammar with semantic actions
expr -> term
expr -> expr + term {print('+');} <- semantic action
expr -> expr - term {print('-');}
term -> 0 {print('0');}
term -> 1 {print('1');}
term -> 2 {print('2');}
...
