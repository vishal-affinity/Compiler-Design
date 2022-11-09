#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void FIRST(char *, char);
void FOLLOW(char *, char);
void addToArray(char *, char);
void printArray(char *);
int searchNt(char *, char);
int searchT(char *, char);

int n;
char production[20][20];
int top = 0;
char stack[20], ip[20];

void push(char c)
{
    if (top >= 20)
        printf("Stack Overflow");
    else
        stack[top++] = c;
}

void pop(void)
{
    if (top < 0)
        printf("Stack underflow");
    else
        top--;
}

void error(void)
{
    printf("\n\nSyntax Error!!!! String is invalid\n");
    getch();
    exit(0);
}

int main()
{
    int i, j = 0, k;
    char c, nt[20], t[20];
    nt[0] = '\0';
    t[0] = '\0';

    FILE *fp = fopen("input.txt", "r");

    printf("\nThe given grammar is:\n");
    fscanf(fp, "%d", &n);
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%s", production[i]);
        printArray(production[i]);
        printf("\n");
        addToArray(nt, production[i][0]);
        for (j = 2; production[i][j] != '\0'; j++) {
            c = production[i][j];
            if (!(isupper(c)) && c != '^') {
                addToArray(t, c);
            }
        }
    }
    addToArray(t, '$');

    fclose(fp);

    int ntCount = 0, tCount = 0;
    while (nt[ntCount] != '\0') {
        ntCount++;
    }
    while (t[tCount] != '\0') {
        tCount++;
    }

    int parseTable[ntCount][tCount];
    for (i = 0; i < ntCount; i++) {
        for (j = 0; j < tCount; j++) {
            parseTable[i][j] = -1;
        }
    }

    for (i = 0; i < n; i++) {
        char result[20];
        result[0] = '\0';
        for (j = 2; production[i][j] != '\0'; j++) {
            c = production[i][j];
            char subResult[20];
            subResult[0] = '\0';
            FIRST(subResult, c);
            int foundEpsilon = 0;
            for (k = 0; subResult[k] != '\0'; k++) {
                if (subResult[k] == '^') {
                    foundEpsilon = 1;
                }
                addToArray(result, subResult[k]);
            }
            if (!foundEpsilon) {
                break;
            }
        }
        if (result[0] == '^') {
            FOLLOW(result, production[i][0]);
        }
        int ntIndex = searchNt(nt, production[i][0]);
        for (k = 0; result[k] != '\0'; k++) {
            int tIndex = searchT(t, result[k]);
            if (parseTable[ntIndex][tIndex] != -1) {
                error();
            }
            parseTable[ntIndex][tIndex] = i;
        }
    }

    printf("\n\nEnter the string to be parsed:\n");
    scanf("%s", ip);

    printf("\n");

    int ipSize = strlen(ip);
    ip[ipSize] = '$';
    ip[ipSize + 1] = '\0';
    push('$');

    push(production[0][0]);

    i = 0;
    while (ip[i] != '\0')
    {
        if (ip[i] == '$' && stack[top - 1] == '$')
        {
            printf("\nSuccessful parsing of string!\n\n");
            return (1);
        }
        else if (ip[i] == stack[top - 1])
        {
            printf("Match of %c occured!\n", ip[i]);
            i++;
            pop();
        }
        else
        {
            char topElement = stack[top - 1];
            char ipElement = ip[i];
            int ntIndex = searchNt(nt, topElement);
            int tIndex = searchT(t, ipElement);
            if (ntIndex == -1 || tIndex == -1) {
                error();
            }
            int pIndex = parseTable[ntIndex][tIndex];
            if (pIndex == -1) {
                error();
            }
            printf("%s\n", production[pIndex]);
            pop();
            k = strlen(production[pIndex]);
            for (j = k - 1; j >= 2; j--) {
                c = production[pIndex][j];
                if (c != '^') {
                    push(c);
                }
            }
        }
    }

    return 0;
}

int searchNt(char *nt, char c) {
    for (int i = 0; nt[i] != '\0'; i++) {
        if (nt[i] == c) {
            return i;
        }
    }
    return -1;
}

int searchT(char *t, char c) {
    for (int i = 0; t[i]!= '\0'; i++) {
        if (t[i] == c) {
            return i;
        }
    }
    return -1;
}

void FIRST(char *Result, char c)
{
    int i, j, k;
    char subResult[20];
    int foundEpsilon;
    subResult[0] = '\0';
    Result[0] = '\0';
    if (!(isupper(c)))
        addToArray(Result, c);
    else
        for (i = 0; i < n; i++)
        {
            if (production[i][0] == c)
            {
                if (production[i][2] == '^')
                    addToArray(Result, '^');
                else
                {
                    for (j = 2; production[i][j] != '\0'; j++)
                    {
                        foundEpsilon = 0;
                        FIRST(subResult, production[i][j]);

                        for (k = 0; subResult[k] != '\0'; k++)
                            if (subResult[k] == '^')
                                foundEpsilon = 1;
                            else
                                addToArray(Result, subResult[k]);
                        if (!foundEpsilon)
                            break;
                    }
                }
            }
        }
    return;
}

void FOLLOW(char *Result, char c)
{
    Result[0] = '\0';
    if (c == production[0][0])
    {
        addToArray(Result, '$');
    }
    for (int i = 0; i < n; i++)
    {
        int done = 0;
        for (int j = 2; production[i][j] != '\0'; j++)
        {
            if (production[i][j] == c)
            {
                // printArray(production[i]);
                // printf("\n");
                if (production[i][j + 1] != '\0')
                {
                    int flag = 1;
                    char first[20];
                    for (int k = j + 1; production[i][k] != '\0' && flag; k++) {
                        flag = 0;
                        first[0] = '\0';
                        FIRST(first, production[i][k]);
                        // printArray(first);
                        // printf("\n");
                        for (int l = 0; first[l] != '\0'; l++) {
                            if (first[l] == '^') {
                                flag = 1;
                            } else {
                                addToArray(Result, first[l]);
                            }
                        }
                    }
                    if (flag)
                    {
                        char follow[20];
                        follow[0] = '\0';
                        FOLLOW(follow, production[i][0]);
                        // printArray(follow);
                        // printf("\n");
                        for (int k = 0; follow[k] != '\0'; k++)
                        {
                            addToArray(Result, follow[k]);
                        }
                    }
                }
                else
                {
                    char follow[20];
                    follow[0] = '\0';
                    FOLLOW(follow, production[i][0]);
                    for (int k = 0; follow[k] != '\0'; k++)
                    {
                        addToArray(Result, follow[k]);
                    }
                }
                done = 1;
                break;
            }
        }
        if (done) break;
    }
}

void addToArray(char *Result, char val)
{
    int k;
    for (k = 0; Result[k] != '\0'; k++)
        if (Result[k] == val)
            return;
    Result[k] = val;
    Result[k + 1] = '\0';
}

void printArray(char *a)
{
    int i = 0;
    for (i = 0; a[i] != '\0'; i++)
        printf("%c ", a[i]);
}
