#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

int size = 0;

char keyword[30][30] = {"int", "while", "break", "for", "do", "if", "float", "char", "switch", "double", "short", "long", "unsigned", "sizeof", "else", "register", "extern", "static", "auto", "case", "break", "volatile", "enum", "typedef"};

char id[20], num[10], op[5];

char symb_tab[50][20];
int idx = 0;

int check_keyword(char s[])
{
    int i;
    for (i = 0; i < 24; i++)
        if (strcmp(s, keyword[i]) == 0)
            return 1;
    return 0;
}

void store_symb_tab(char id[], char symb_tab[][20])
{
    int flag = 0, i;
    for (i = 0; i < idx; i++)
    {
        if (strcmp(id, symb_tab[i]) == 0)
        {
            flag = 1;
        }
    }
    if (flag == 0)
    {
        strcpy(symb_tab[idx], id);
        idx++;
    }
}

void main()
{
    FILE *fp1, *fp2;
    char c;
    int state = 0;
    int i = 0, j = 0, k = 0;
    fp1 = fopen("x.txt", "r"); // input file containing src prog
    fp2 = fopen("y.txt", "w"); // output file name

    while ((c = fgetc(fp1)) != EOF)
    {
        switch (state)
        {
        case 0:
            if (isalpha(c))
            {
                state = 1;
                id[i++] = c;
            }
            else if (isdigit(c))
            {
                state = 3;
                num[j++] = c;
            }
            else if (c == '<' || c == '>')
            {
                state = 5;
                op[k++] = c;
            }
            else if (c == '=' || c == '!')
            {
                state = 8;
                op[k++] = c;
            }
            else if (c == '/')
                state = 10;
            else if (c == ' ' || c == '\t' || c == '\n')
                state = 0;
            else
                fprintf(fp2, "\n%c", c);
            break;
        case 1:
            if (isalnum(c))
            {
                state = 1;
                id[i++] = c;
            }
            else
            {
                id[i] = '\0';
                if (check_keyword(id))
                    fprintf(fp2, "\n%s : keyword ", id);
                else
                {
                    fprintf(fp2, "\n%s : identifier", id);
                    store_symb_tab(id, symb_tab);
                }
                // call a function which stores id in symbol table

                state = 0;
                i = 0;
                ungetc(c, fp1);
            }
            break;
        case 3:
            if (isdigit(c))
            {
                num[j++] = c;
                state = 3;
            }
            else
            {
                num[j] = '\0';
                fprintf(fp2, "\n%s: number", num);
                state = 0;
                j = 0;
                ungetc(c, fp1);
            }
            break;
        case 5:
            if (c == '=')
            {
                // write code to print specific operator like <= or >=
                state = 0;
            }
            else
            {
                // write code to print specific operator like <, >, <= or >=
                state = 0;
                ungetc(c, fp1);
            }
            op[k++] = c;
            op[k] = '\0';
            fprintf(fp2, "\n%s : relational operator ", op);
            k = 0;
            break;
        case 8:
            if (c == '=')
            {
                op[k++] = c;
                op[k] = '\0';
                fprintf(fp2, "\n%s : relational operator ", op);
                k = 0;
                // write code to print specific operator like == or !=
                state = 0;
            }
            else
            {
                ungetc(c, fp1);
                state = 0;
            }
            break;
        case 10:
            if (c == '*')
                state = 11;
            else
                fprintf(fp2, "\ninvalid lexeme");
            break;
        case 11:
            if (c == '*')
                state = 12;
            else
                state = 11;
            break;
        case 12:
            if (c == '*')
                state = 12;
            else if (c == '/')
                state = 0;
            else
                state = 11;
            break;

        } // End of switch
    }     // end of while
    if (state == 11)
        fprintf(fp2, "comment did not close");
    fclose(fp1);
    fclose(fp2);
}
