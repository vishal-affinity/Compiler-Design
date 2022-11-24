%{
#include<stdio.h>
%}
%token NUMBER
%%
S: E { printf("The result is =%d\n",$1);}
;
E: E'+'T { $$ = $1 + $3; }
| T { $$ = $1;}
;
T: T'*'F { $$ = $1 * $3; }
| F { $$ = $1;}
;
F: '('E')' { $$ = $2;}
| NUMBER { $$ = $1;}
;
%%
int main(){
yyparse();
}
int yywrap(){
return 1;
}
void yyerror(char *s){
printf("Error %s",s);
}
