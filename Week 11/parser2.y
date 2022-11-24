%{
#include<stdio.h>
%}
%token DIGIT
%left '-' '+'
%left '*' '/'
%nonassoc UMINUS
%%
S: E { printf("The result is =%d\n",$1);}
;
E: E'+'E { $$ = $1 + $3; }
| E'-'E { $$ = $1 - $3; }
| E'*'E { $$ = $1 * $3; }
| E'/'E { if($3 == 0)

yyerror("Divide by zero");
else
$$ = $1 / $3; }
| '-'E %prec UMINUS { $$ = -$2; }
| '(' E ')' { $$ = $2; }
| DIGIT {$$ = $1;}
;
%%
int main()
{
yyparse();
}
int yywrap(){
return 1;
}
void yyerror(char *s){
printf("Error %s",s);exit(0);
}
