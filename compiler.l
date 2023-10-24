%option noyywrap
%{
#include "y.tab.h"    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void yyerror(char *s);
%}

DIGIT    [0-9]
DEC      {DIGIT}+(\.{DIGIT}+)
INT      {DIGIT}+

LETTER   [a-zA-Z]
NAME     {LETTER}({LETTER}|{DIGIT})*
STRING   ["][^"]+["]

%%

"+"         {return '+';}
"-"         {return '-';}
"*"         {return '*';}
"/"         {return '/';}
"**"        {return power;}

"("         {return '(';}
")"         {return ')';}
"{"         {return '{';}
"}"         {return '}';}

"="         {return '=';}
">"         {return '>';}
">="        {return greater_equal;}
"<"         {return '<';}
"<="        {return smaller_equal;}

"="{DEC}"=" {yylval.double_val = atof(yytext + 1); return almost_equals;}
"=C="       {return strequals_nsens;}
"=="        {return EQUALS;}

"if"        {return IF;}
"else"      {return ELSE;}

"true"      {return TRUE;}
"false"     {return FALSE;}

"table"     {return symbols_table;} 

"print"     {return PRINT;}
"exit"      {return EXIT;}

";"        {return ';';}

"int"       {return int_dec;}
"dec"       {return dec_dec;}
"bool"      {return bool_dec;}
"string"    {return string_dec;}

{DEC}       {yylval.double_val = atof(yytext); return DEC;}
{INT} 	    {yylval.int_val = atoi(yytext); return INT;}
{NAME}      {yylval.string_val = strdup(yytext); return NAME;}
{STRING}    {yylval.string_val = strdup(yytext); return STRING;}

[ \n\t]       {;} 
.           {yyerror("Illegal character, you are under arrest\n");}
%%