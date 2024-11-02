#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main()
{
    while(1)
    {
        char user_input[100];
	    printf("> ");
        fgets(user_input,sizeof(user_input),stdin);
        size_t len = strlen(user_input);
        if(len > 0 && user_input[len-1] == '\n')
        {
        user_input[len - 1] = '\0';
        }
        if(strcmp(user_input, "exit") == 0)
        {
            break;
        }
        pid_t pid = fork();
        if(pid < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (pid == 0)
        {
            char *args[] = {"/bin/sh", "-c", user_input, NULL}; 
            execvp(args[0], args);
            perror("exec failed");
            exit(1);
        }
        else
        {
            wait(NULL);
        }
    }
    return 0;
}