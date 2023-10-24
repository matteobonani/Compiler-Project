%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "operationHandler.h"
#include "symbolTable.h"
#include "node.h"
#include "comparisonHandler.h"

void yyerror(char *s);
int yylex(void); 
void printST(struct nodeValue* node);
%}

%union{
    int int_val;
    double double_val;
    char* id;
    char* string_val;
    struct nodeValue* value;
}

%start line

%token <int_val> INT
%token <double_val> DEC
%token <id> NAME
%token <string_val> STRING
%token <double_val> almost_equals
%token symbols_table
%token strequals_nsens
%token int_dec dec_dec bool_dec string_dec 
%token greater_equal smaller_equal
%token EQUALS   
%token TRUE FALSE
%token PRINT
%token IF ELSE
%token EXIT


%type <int_val> line
%type <value> expr boolean conditions
%type <id> statement assignment if_block else_block

%left '<' '>' '='
%left '+' '-'   
%left '*' '/'
%left power

%%

line        : line statement      {;}
            | statement           {;}
            ;
          
statement   : EXIT                   {exit(1);}
            | symbols_table ';'      {printSymbolTable();} 
            | PRINT expr ';'         {printST($2);} 
            | PRINT conditions ';'   {printST($2);}      
            | assignment ';'         {;}
            | if_block               {;}
            ;

expr        : DEC                           {$$ = create_double_node($1);}
            | INT                           {$$ = create_int_node($1);}
            | NAME                          {$$ = searchNode($1);}
            | STRING                        {$$ = create_string_node($1);}
            | expr '+' expr                 {$$ = doOperation($1,$3, '+');}
            | expr '-' expr                 {$$ = doOperation($1,$3, '-');}
            | expr '*' expr                 {$$ = doOperation($1,$3, '*');}
            | expr '/' expr                 {$$ = doOperation($1,$3, '/');}
            | expr power expr               {$$ = doOperation($1,$3, 'p');}
            | '(' expr ')'                  {$$ = $2;}
            ;

conditions  : expr '>' expr                 {$$ = doComparison($1, $3, ">");}
            | expr greater_equal expr       {$$ = doComparison($1, $3, ">=");}
            | expr '<' expr                 {$$ = doComparison($1, $3, "<");}
            | expr smaller_equal expr       {$$ = doComparison($1, $3, "<=");}
            | expr almost_equals expr       {$$ = isEqualWithTolerance($1, $3, $2);}
            | expr strequals_nsens expr     {$$ = doComparison($1, $3, "=C=");}
            | expr EQUALS expr              {$$ = doComparison($1, $3, "==");}
            | boolean                       {;}
            ;    

if_block    : IF '(' conditions ')' conditional_block                  {printf("Found IF block \n");}
	        | IF '(' conditions ')' conditional_block else_block       {;}
	        ;

else_block  : ELSE conditional_block        {printf("ELSE block\n");}
            | ELSE if_block                 {printf("ELSE-IF block\n");}
		    ;

conditional_block : open_curly line close_curly                {;}


open_curly:     '{'     {increaseLevel();}

close_curly:    '}'     {decreaseLevel();}
assignment  : int_dec NAME '=' expr 	        {insertAtBeginning(create_node($4, 'i'), $2);}
            | dec_dec NAME '=' expr  	        {insertAtBeginning(create_node($4, 'd'), $2);}
            | bool_dec NAME '=' conditions 	    {insertAtBeginning(create_boolean_node($4), $2);}
            | string_dec NAME '=' expr  	    {insertAtBeginning(create_node($4, 's'), $2);}  
            | NAME '=' expr                     {updateNode($3,$1);}            
            ;   

boolean     : TRUE              {$$ = create_boolean_node(1);}
            | FALSE             {$$ = create_boolean_node(0);}
            ;
%%

int main() {
    yyparse();
}

void yyerror(char* s) {
    fprintf(stderr, "\033[1;31mError: %s\033[0m\n", s);
    exit(1);
}

void printST(struct nodeValue* node){

    if(node->type == STRING_TYPE){
        printf("%s\n",node->value.string);
    }else if (node->type == INT_TYPE){
        printf("%d\n",node->value.integer);
    }else if (node->type == DOUBLE_TYPE){
        printf("%f\n",node->value.decimal);
    }else{
       printf("%s\n", node->value.boolean ? "true" : "false");
    }

}

