%{
#include<stdio.h>
#include<string.h>
struct quad
{
char op[5];
char arg1[10];
char arg2[10];
char result[10];
}QUAD[30];
int i=0,j;
%}
%union
{
char exp[10];
}
%token <exp> VAR
%type <exp> S E T F
%%
S: E { printf("\n THere are %d quadrupls n",i);
printf("\n List of Quadruples are: \n");
for(j=0;j<i;j++)

printf("%s\t%s\t%s\t%s\n",QUAD[j].op,QUAD[j].arg
1,QUAD[j].arg2,QUAD[j].result);

}
;
E: E'+'T { printf("\n E ->E+T, $1=%s,
$3=%s,$$=%s\n",$1,$3,$$);
strcpy(QUAD[i].op,"+");
strcpy(QUAD[i].arg1,$1);
strcpy(QUAD[i].arg2,$3);
strcpy(QUAD[i].result,$$);i++;
i++;
}
| T { printf("\n E -> T, $1=%s, $$=%s\n",$1,$$);}
;
T: T'*'F { printf("\n T -> T*F, $1=%s, $3=%s,
$$=%s\n",$1,$3,$$);
strcpy(QUAD[i].op,"*");
strcpy(QUAD[i].arg1,$1);
strcpy(QUAD[i].arg2,$3);
strcpy(QUAD[i].result,$$);
i++;
}
| F { printf("\n T -> F, $1=%s, $$=%s\n",$1,$$);}
;

F: VAR {printf("\n F ->VAR and $1=%s, $$=%s \n",$1,$$);}
;
%%
main()
{
yyparse();
}
int yywrap(){
return 1;
}
void yyerror(char *s)
{
printf("%s",s);
}
