%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex();
extern FILE *yyin;

void yyerror(const char *s);

struct row_entry {
    char *name;
    struct row_entry *first_child;
    struct row_entry *next_sibling;
};

static struct row_entry* cons(const char* name, struct row_entry* first_child) {
    struct row_entry* node = malloc(sizeof(struct row_entry));
    if (!node) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1);
    }
    node->name = strdup(name);
    node->first_child = first_child;
    node->next_sibling = NULL;
    return node;
}

static void display(struct row_entry* node, int depth) {
    if (!node) return;
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    printf("%s\n", node->name);
    display(node->first_child, depth + 1);
    display(node->next_sibling, depth);
}

static void free_row_entry(struct row_entry* node) {
    if (!node) return;
    free_row_entry(node->first_child);
    free_row_entry(node->next_sibling);
    free(node->name);
    free(node);
}
%}


%union {
    struct row_entry* row;
    int int_val;
    float float_val;
    char* str_val;
}

%type <row> program statement_list statement assignment_statement if_statement 
while_statement io_statement declaration_statement type array_type default_type 
expression_list expression term factor condition relational_operator
%token <int_val> INTEGER_CONSTANT
%token <float_val> FLOAT_CONSTANT
%token <str_val> STRING_CONSTANT IDENTIFIER
%token IF ELSE WHILE READ WRITE INT FLOAT STRING CHAR ARRAY OF
%token LPAREN RPAREN LBRACE RBRACE LBRACKET RBRACKET SEMICOLON COMMA ASSIGN
%token PLUS MINUS MULTIPLY DIVIDE MODULO EQUALS NOTEQUAL LT GT LTE GTE AND OR

%%

program:
    statement_list { display($1, 0); free_row_entry($1); }
;

statement_list:
    statement 
    { $$ = cons("statement_list", $1); }
    | statement statement_list
     { $$ = cons("statement_list", $1); $1->next_sibling = $2; }
;

statement:
    assignment_statement 
    { $$ = cons("assignment_statement", $1); }
    | if_statement 
      { $$ = cons("if_statement", $1); }
    | while_statement 
      { $$ = cons("while_statement", $1); }
    | io_statement 
      { $$ = cons("io_statement", $1); }
    | declaration_statement 
      { $$ = cons("declaration_statement", $1); }
;

assignment_statement:
    IDENTIFIER ASSIGN expression SEMICOLON 
    { $$ = cons("assignment_statement", cons($1, $3)); }
;

if_statement:
    IF LPAREN condition RPAREN LBRACE statement_list RBRACE 
    { $$ = cons("if", $3); $3->next_sibling = $6; }
    | IF LPAREN condition RPAREN LBRACE statement_list RBRACE 
      ELSE LBRACE statement_list RBRACE 
     { $$ = cons("if-else", $3); $3->next_sibling = $6; $6->next_sibling = $10; }
;

while_statement:
    WHILE LPAREN condition RPAREN LBRACE statement_list RBRACE 
    { $$ = cons("while", $3); $3->next_sibling = $6; }
;

io_statement:
    WRITE LPAREN expression_list RPAREN SEMICOLON { $$ = cons("write", $3); }
    | READ LPAREN IDENTIFIER RPAREN SEMICOLON { $$ = cons("read", cons($3, NULL)); }
;

declaration_statement:
    type IDENTIFIER SEMICOLON 
    { $$ = cons("declaration_statement", cons($2, NULL)); }
    | type IDENTIFIER ASSIGN expression SEMICOLON 
      { $$ = cons("declaration_statement_with_assignment", cons($2, $4)); }
;

type:
    INT { $$ = cons("INT", NULL); }
    | FLOAT { $$ = cons("FLOAT", NULL); }
    | STRING { $$ = cons("STRING", NULL); }
    | CHAR { $$ = cons("CHAR", NULL); }
    | array_type { $$ = cons("array_type", $1); }
;

array_type:
    ARRAY LBRACKET INTEGER_CONSTANT RBRACKET OF default_type 
    { $$ = cons("array_type", 
            cons("ARRAY", 
            cons("LBRACKET", 
            cons("INTEGER_CONSTANT",
             cons("RBRACKET", 
             cons("OF", $6)))))); }
;

default_type:
    INT { $$ = cons("INT", NULL); }
    | FLOAT { $$ = cons("FLOAT", NULL); }
    | STRING { $$ = cons("STRING", NULL); }
    | CHAR { $$ = cons("CHAR", NULL); }
;

expression_list:
    expression { $$ = cons("expression_list", $1); }
    | expression COMMA expression_list 
      { $$ = cons("expression_list", $1); $1->next_sibling = $3; }
;

expression:
    term { $$ = cons("expression", $1); }
    | expression PLUS term { $$ = cons("+", $1); $1->next_sibling = $3; }
    | expression MINUS term { $$ = cons("-", $1); $1->next_sibling = $3; }
;

term:
    factor { $$ = cons("term", $1); }
    | term MULTIPLY factor { $$ = cons("*", $1); $1->next_sibling = $3; }
    | term DIVIDE factor { $$ = cons("/", $1); $1->next_sibling = $3; }
    | term MODULO factor { $$ = cons("%", $1); $1->next_sibling = $3; }
;

factor:
    IDENTIFIER { $$ = cons($1, NULL); }
    | INTEGER_CONSTANT { $$ = cons("int_const", NULL); }
    | FLOAT_CONSTANT { $$ = cons("float_const", NULL); }
    | STRING_CONSTANT { $$ = cons("string_const", NULL); }
    | LPAREN expression RPAREN { $$ = $2; }
;

condition:
    expression relational_operator expression 
    { $$ = cons("condition", $1); $1->next_sibling = $3; }
;

relational_operator:
    EQUALS { $$ = cons("==", NULL); }
    | NOTEQUAL { $$ = cons("!=", NULL); }
    | LT { $$ = cons("<", NULL); }
    | GT { $$ = cons(">", NULL); }
    | LTE { $$ = cons("<=", NULL); } 
    | GTE { $$ = cons(">=", NULL); } 
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Error opening file");
            return 1;
        }
        yyin = file;
    }

    yyparse();

    if (argc > 1) {
        fclose(yyin);
    }

    return 0;
}
