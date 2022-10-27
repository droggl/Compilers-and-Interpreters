# Lab-2


~~~
start -> list eof
list -> assignment ; list
	 | expr ; list
       | empty
assignment -> id { print(id.lexeme) } = expr { print('=') }
expr -> term moreterms
moreterms -> + term { print('+') } moreterms
       | - term { print('-') } moreterms
       | empty
term -> factor morefactors
morefactors -> * factor { print('*') } morefactors
       | / factor { print('/') } morefactors
       | div factor { print('DIV') } morefactors
       | mod factor { print('MOD') } morefactors
       | empty
factor -> ( expr )
       | id { print(id.lexeme) }
       | num { print(num.value) }
~~~