#include <stdio.h>

int main()
{
    // Write C code here
    int state = 0;
    int n;
    printf("Enter the size of the input string\n");
    scanf("%d",&n);
    char aa[n];
    printf("Enter the string with a and b only\n");
    scanf("%s",&aa);
    int y=0;
    while(y != n)
    {
        char var = aa[y];
        if(var == 'a' || var == 'b')
        {
            switch(state)
            {
                case 0:
                {
                    if(var == 'a')
                    {
                        state = 1;
                    }
                    else
                    {
                        state = 3;
                    }
                    break;
                }
                case 1:
                {
                    if(var == 'a')
                    {
                        state = 0;
                    }
                    else
                    {
                        state = 2;
                    }
                    break;
                }
                case 2:
                {
                    if(var == 'a')
                    {
                        state = 3;
                    }
                    else
                    {
                        state = 1;
                    }
                    break;
                }
                case 3:
                {
                    if(var == 'a')
                    {
                        state = 2;
                    }
                    else
                    {
                        state = 0;
                    }
                    break;
                }
                default:
                {
                    printf("The string cannot be determined\n");
                }
            }
        }
        else
        {
            printf("please enter a valid string with a and b only\n");
            state = -1;
            break;
        }
        y++;
    }
    if(state == -1)
    {
        return;
    }
    else
    {
        if(state == 0)
        {
            printf("Congrats your string accepted\n");
        }
        else
        {
            printf("Sorry string not accepted\n");
        }
    }

    return 0;
}
