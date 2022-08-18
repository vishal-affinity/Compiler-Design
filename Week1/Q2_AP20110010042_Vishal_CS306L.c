#include <stdio.h>

int main() {
    // Write C code here
    int state=0,i=0;
    char t,s[20];
    printf("Enter input string \t :");
    scanf("%s",s);
    while((t=s[i++])!='\0')
    {
        switch(state)
        {
            case 0:
            if(t=='a')
            {
                state=1;
            }
            else if(t=='b')
            {
                state=3;
            }
            else{
                printf("error");
                exit(0);
            }
            break;
            case 1:
            if(t=='a')
            {
                state=2;
            }
            else if(t=='b')
            {
                state=3;
            }
            else{
                printf("error");
                exit(0);
            }
            break;
            case 2:
            if(t=='a')
            {
                state=2;
            }
            else if(t=='b')
            {
                state=3;
            }
            else{
                printf("error");
                exit(0);
            }
            break;
            case 3:
            if(t=='a')
            {
                state=1;
            }
            else if(t=='b')
            {
                state=4;
            }
            else{
                printf("error");
                exit(0);
            }
            break;
            case 4:
            if(t=='a')
            {
                state=1;
            }
            else if(t=='b')
            {
                state=4;
            }
            else{
                printf("error");
                exit(0);
            }
            break;
            
        }
    }
    if(state==2||state==4)
        printf("\n\nString accepted\n\n");
    else
        printf("\n\nString not accepted\n\n");

    return 0;
}
