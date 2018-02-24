%{


/* This interpreter evaluates arithmetic expressions and assigns
   them to the specified variable names. The grammar is:

   pgm -> stmtlist
   stmtlist -> stmt | stmtlist ; stmt
   stmt -> id = logconj | print id | read id 
         | if (compopt) {stmtlist} else {stmtlist} 
         | while(logconj) {stmtlist}
   logconj -> logconj || logdisj | logdisj | exp
   logdisj -> logdisj && logneg | logneg
   logneg -> !compopt | compopt
   compopt -> exp == exp | exp != exp
            | exp >= exp | exp <= exp
            | exp >  exp | exp <  exp
   exp -> exp + mulexp | exp - mulexp 
   mulexp -> mulexp * primexp | mulexp / primexp
   primexp ->  ( logconj ) | - primexp | id | number 
*/

#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include "imp.h"

using namespace std;

 extern FILE *yyin;

// the root of the abstract syntax tree
 stmt_node *root;

// for keeping track of line numbers in the program we are parsing
  int line_num = 1;

// function prototypes, we need the yylex return prototype so C++ won't complain
int yylex();
void yyerror(const char* s);

%}

%start program

%union {
  float number;
  char * var_name;
  exp_node *exp_node_ptr;
  stmt_node *stmt_node_ptr;
}

%error-verbose

/*
 * MODIFY(ADD): In the token section i added a couple new constant tokens shown bellow
 * - READ (read)
 * - OR (||)
 * - AND (&&)
 * - NOT (!)
 * - BOOLEQUAL (==)
 * - BOOLGREATEREQUAL (>=)
 * - BOOLLESSEQUAL (<=)
 * - BOOLGREATER (>)
 * - BOOLLESS (<)
 * - BOOLNOTEQUAL (!=)
 * - IF (if)
 * - ELSE (else)
 * - WHILE (while)
 *
 * Also I have added 4 more nodes that are exp nodes listed bellow
 * - logconj (OR,||)
 * - logdisj (AND,&&)
 * - logneg (NOT,!)
 * - compopt (==, !=, etc.)
 */

%token <number> NUMBER
%token <var_name> ID
%token SEMICOLON  EQUALS PRINT READ  PLUS MINUS TIMES DIVIDE  LPAREN RPAREN LBRACE RBRACE OR AND NOT BOOLEQUAL BOOLGREATEREQUAL BOOLLESSEQUAL BOOLGREATER BOOLLESS BOOLNOTEQUAL IF ELSE WHILE
%type <exp_node_ptr> logconj
%type <exp_node_ptr> logdisj
%type <exp_node_ptr> logneg
%type <exp_node_ptr> compopt
%type <exp_node_ptr> exp
%type <exp_node_ptr> mulexp
%type <exp_node_ptr> primexp 
%type <stmt_node_ptr> stmtlist
%type <stmt_node_ptr> stmt
%type <stmt_node_ptr> program

%%

program : stmtlist { root = $$; }
;

stmtlist : stmtlist SEMICOLON stmt { // copy up the list and add the stmt to it
  $$ = new sequence_node($1,$3);
}
| 
stmtlist SEMICOLON error { // just copy up the stmtlist when an error occurs
  $$ = $1;
  yyclearin; 
} 
| stmt { $$ = $1; }
;

/*
 * MODIFY(UPDATE)
 * In the grammer i have add 3 new grammer conditions
 * - ID EQUALS logconj (So that variables can equal booleans expretions)
 * - READ ID (reads in number to variable)
 * - IF-ELSE (IF logconj is true else statments)
 * - WHILE (WHILE true run statments)
 */

stmt: ID EQUALS logconj { 
  $$ = new assign_node($1, $3);
}
| PRINT exp {
  $$ = new print_node($2);
}
| READ ID {
  $$ = new read_node($2);
}
| IF LPAREN logconj RPAREN stmt ELSE stmt {
  $$ = new if_else_node($3, $5, $7);
}
| WHILE LPAREN logconj RPAREN stmt {
  $$ = new while_node($3, $5);
}
| { 
  $$ = new skip_node();
}
| LBRACE stmtlist RBRACE { $$=$2; } 
;

/*
 * MODIFY(ADD)
 * In the grammer there are 4 new boolean exp
 * - logconj (logic conjunction)
 * - logdisj (logic disjunction)
 * - logneg (logic negitive)
 * - compopt (exp compare operators)
 */
logconj: logconj OR logdisj { $$ = new or_node($1, $3); }
| logdisj { $$ = $1; }
| exp { $$ = $1; }
;
logdisj: logdisj AND logneg { $$ = new and_node($1, $3); }
| logneg { $$ = $1; }
;

logneg: NOT compopt { $$ = new not_node($2); }
| compopt { $$ = $1; }
;

compopt : exp BOOLEQUAL exp { $$ = new bool_equal_node($1, $3); }
| exp BOOLGREATEREQUAL exp { $$ = new bool_greater_equal_node($1, $3); }
| exp BOOLLESSEQUAL exp { $$ = new bool_less_equal_node($1, $3); }
| exp BOOLGREATER exp { $$ = new bool_greater_node($1, $3); }
| exp BOOLLESS exp { $$ = new bool_less_node($1, $3); }
| exp BOOLNOTEQUAL exp { $$ = new bool_not_equal_node($1, $3); }
| exp { $$ = $1; }
;

exp:	exp PLUS mulexp { $$ = new add_node($1, $3); }
| exp MINUS mulexp { $$ = new subtract_node($1, $3); } |	mulexp {  $$ = $1; }
;

mulexp:	mulexp TIMES primexp {
  $$ = new multiply_node($1, $3); 
}
| mulexp DIVIDE primexp {
	$$ = new divide_node($1, $3); 
}
| primexp { $$=$1;  }
;

/*
 * MODIFY(UPDATE)
 * Changed (exp) to (logconj) so that the primexp can point back to the top of the grammer
 */
primexp: MINUS primexp { $$ = new neg_node($2); }
| LPAREN logconj RPAREN  {  $$ = $2; }
|	NUMBER { $$ = new number_node($1); }
| ID { $$ = new variable_node($1); }
;
 
%%
int main(int argc, char **argv)
{ 
  if (argc>1) yyin=fopen(argv[1],"r");

  //  yydebug = 1;
  yyparse();

  cout << "---------- list of input program------------" << endl << endl;

  root -> print();

  cout << "---------- exeuction of input program------------" << endl << endl;
  

  root->evaluate();
}

void yyerror(const char * s)
{
  fprintf(stderr, "line %d: %s\n", line_num, s);
}

