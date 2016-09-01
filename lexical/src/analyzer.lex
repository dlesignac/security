
%option noyywrap

%{
#include <stdio.h>
#include <stdlib.h>

%}
signature1		74657374
signature2		87e6df
signature3		98a2b6

%%
{signature1}		printf("spotted signature 1\n");
{signature2}		printf("spotted signature 2\n");
{signature3}		printf("spotted signature 3\n");
[a-eA-E0-9]			;

%%
int main()
{
	yylex();
}
