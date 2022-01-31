#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    while(1)
    {
        if(fork()== 0)
        {
            printf("\033[32m$ ");
            printf("\033[0m");
            char * prog = malloc(100000*sizeof(char *));

            // https://stackoverflow.com/questions/27015857/weird-behaiviour-of-scanf-in-c
            // space is need before % below
            
            scanf(" %100000[^\n]",prog);
            int count = 0;

            int n=0;
            while(prog[n] != '\0')
            {
                n++;
            }

            for(int i=0;i<n;i++)
            {
                if(prog[i] == ' ')
                {
                    count++;
                }
            }

            char * params[100];

            params[0] = &prog[0];

            int j=0,i;
            for(i=0;i<count;i++)
            {
                while(prog[j] != ' ' && j<n)
                {
                    j++;
                }
                prog[j]='\0';
                j++;
                params[i+1] = &prog[j];
            }

            params[i+1] = NULL;
            if(strcmp(params[0],"exit") == 0)
            {
                printf("\033[32m");
                printf("Bye!\n");
                printf("\033[0m");

                exit(1);           /* terminate child */
            }
            execv(params[0], params);
            printf("Failed\n");
            free(prog);
        }
        else
        {
            int *status = malloc(1*sizeof(int *));
            wait(status);
            //printf("%d\n",*status);
            if(*status != 0)
            {
                free(status);
                exit(0);
            }
            free(status);
        }
    }
    printf("end is near");
    return 0;
}