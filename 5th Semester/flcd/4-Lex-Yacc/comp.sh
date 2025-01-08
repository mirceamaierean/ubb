# /bin/bash
flex lang.lxi
yacc -d lang.y
gcc lex.yy.c y.tab.c -o parser -ll