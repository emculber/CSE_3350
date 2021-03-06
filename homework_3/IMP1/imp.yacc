%{


/* This interpreter evaluates arithmetic expressions and assigns
   them to the specified variable names. The grammar is:

   pgm -> stmtlist
   stmtlist -> stmt | stmtlist ; stmt
   stmt -> id = exp 
        |  print id
   exp -> exp + mulexp | exp - mulexp 
   mulexp -> mulexp * primexp | mulexp / primexp
   primexp ->  ( exp ) | ( exp ) | - primexp | id | number 
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

%token <number> NUMBER
%token <var_name> ID
%token SEMICOLON  EQUALS PRINT  PLUS MINUS TIMES DIVIDE  LPAREN RPAREN LBRACE RBRACE
%type <exp_node_ptr> exp
%type <exp_node_ptr> mulexp
%type <exp_node_ptr> primexp 
%type <stmt_node_ptr> stmtlist
%type <stmt_node_ptr> stmt
%type <stmt_node_ptr> program

%%

program : stmtlist { root = $$; }
;

stmtlist : stmtlist SEMICOLON stmt
            { // copy up the list and add the stmt to it
              $$ = new sequence_node($1,$3);
            }
         | stmtlist SEMICOLON error
	   { // just copy up the stmtlist when an error occurs
             $$ = $1;
             yyclearin; } 
         |  stmt 
	 { $$ = $1;   }
;

stmt: ID EQUALS exp { 
  $$ = new assign_node($1, $3);
	   }
       
| PRINT exp {
  $$ = new print_node($2);
 }

|
{ $$ = new skip_node();
}
| LBRACE stmtlist RBRACE { $$=$2; } 
 ;


exp:	exp PLUS mulexp { $$ = new add_node($1, $3); }

      |	exp MINUS mulexp { $$ = new subtract_node($1, $3); }

      |	mulexp {  $$ = $1; }
;



mulexp:	mulexp TIMES primexp {
	  $$ = new multiply_node($1, $3); }

      | mulexp DIVIDE primexp {
	  $$ = new divide_node($1, $3); }

      | primexp { $$=$1;  }
;



primexp:	MINUS primexp  { $$ = new neg_node($2); }

      |	LPAREN exp RPAREN  {  $$ = $2; }

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

