%option interactive
%{
/* * * * * * * * * * * *
 * * * DEFINITIONS * * *
 * * * * * * * * * * * */
%}

%{

// y.tab.h contains the token number values produced by the parser
#include <string.h>
#include "imp.h"
#include "y.tab.h"

extern int line_num;

%}


%option noyywrap
DIGIT [0-9]
LETTER [a-zA-Z]

%{ 
  /* * * * * * * * * *
   * * * STATES  * * *
   * * * * * * * * * */
%}

%x ERROR

%%

%{
/* * * * * * * * * 
 * * * RULES * * *
 * * * * * * * * */
%}

print   { return PRINT; }
read    { return READ; } // MODIFY(ADD): This was added for the input statement
if      { return IF; }   // MODIFY(ADD): This was added for the if else loop
else    { return ELSE; } // MODIFY(ADD): This was added for the if else loop
while   { return WHILE; }// MODIFY(ADD): This was added for the while loop
{DIGIT}+ {
	yylval.number = atof(yytext); return NUMBER;
	}

{LETTER}[0-9a-zA-Z]* {
        yylval.var_name = strdup(yytext); return ID;
	}

[ \t\f\r]	;		 // ignore white space 

\n   { line_num++;              }
"-"	 { return MINUS;            }
"+"	 { return PLUS;             }
"*"	 { return TIMES;            }
"/"	 { return DIVIDE;           }
"("	 { return LPAREN;           }
")"	 { return RPAREN;           }
"{"	 { return LBRACE;           }
"}"	 { return RBRACE;           }
"="  { return EQUALS;           }
";"  { return SEMICOLON;        }
"||" { return OR;               } // MODIFY(ADD): Needed for or logic
"&&" { return AND;              } // MODIFY(ADD): Needed for and logic
"!"  { return NOT;              } // MODIFY(ADD): Needed for not logic
"==" { return BOOLEQUAL;        } // MODIFY(ADD): Needed for exp equal exp
">=" { return BOOLGREATEREQUAL; } // MODIFY(ADD): Needed for exp greater or equal to exp
"<=" { return BOOLLESSEQUAL;    } // MODIFY(ADD): Needed for exp less the or equal to exp
">"  { return BOOLGREATER;      } // MODIFY(ADD): Needed for exp greater then exp
"<"  { return BOOLLESS;         } // MODIFY(ADD): Needed for exp less then exp
"!=" { return BOOLNOTEQUAL;     } // MODIFY(ADD): Needed for exp not equal to exp

. { BEGIN(ERROR); yymore(); }
<ERROR>[^{DIGIT}{LETTER}+\-/*(){}= \t\n\f\r] { yymore(); }
<ERROR>(.|\n) { yyless(yyleng-1); printf("error token: %s on line %d\n", yytext, line_num); 
           BEGIN(INITIAL); }

%%

