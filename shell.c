#include "shell.h"
#include "builtins.h"
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h> 


void shell_execute(Command *cmd) {

    if (cmd->argc == 0) return;

    if (cmd->pipe_count > 0) {
        
        int pipe_index = -1;

        for(int i = 0; i< cmd->argc; i++) {
            if(strcmp(cmd->args[i], "|") == 0) {
                pipe_index = i;
                break;
            }
        }

        if(pipe_index == -1) {
            printf("pipe error\n");
            return;
        }

        Command left;
        Command right;

        reset_command(&left);
        reset_command(&right); 

        for(int i = 0; i< pipe_index; i++) {
            left.args[left.argc] = cmd->args[i];
            left.argc++;
        }

        left.args[left.argc] = NULL;

        for(int i = pipe_index +1; i < cmd->argc; i++) {
            right.args[right.argc] = cmd->args[i];
            right.argc++;
        }

        right.args[right.argc] = NULL;

        shell_execute_pipe(&left, &right);

        return;


    }

    if(is_builtin(cmd)) {
       execute_builtin(cmd);
       return;
    }

    pid_t pid = fork();

    if (pid == 0) {
       
        // fils

        if(cmd->input_file != NULL) {
            int fd = open(cmd->input_file, O_RDONLY);

            if (fd < 0) {
                perror("open input");
                exit(1);
            }
            
            dup2(fd,STDIN_FILENO);
            close(fd);
        
        }
        
        if(cmd->output_file != NULL) {
            int fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);

            if (fd < 0) {
                perror("open output ");
                exit(1);
            }
            
            dup2(fd, STDOUT_FILENO);
            close(fd);
        
        }

        execvp(cmd->args[0], cmd->args);
        perror("execvp");
        exit(1);
    } else if (pid > 0) {
        //pere
        wait(NULL);
    } else{
        perror("fork");
    }

}

void shell_run(void) {
    char input[MAX_INPUT];

    Command cmd;

    while(1) {

        printf("mysh$ ");
        fflush(stdout);

        if(fgets(input, MAX_INPUT, stdin) == NULL) {
            printf("\n");
            break;
        }

        parse_command(input, &cmd);

        shell_execute(&cmd);
    }
}

void shell_execute_pipe(Command *left , Command *right) {

    int fd[2];


    if(pipe(fd) == -1) {
        perror("pipe");
        return;
    }

    pid_t pid1 = fork();

    if (pid1 == 0) {
        //fils 1 : commande gauche 

        dup2(fd[1] , STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execvp(left->args[0], left->args);
        
        perror("execvp left");
        exit(1);

    }

    pid_t pid2 = fork();

    if(pid2 == 0) {
        //fils 2 : commande droite 

        dup2(fd[0], STDIN_FILENO);

        close(fd[1]);
        close(fd[0]);

         execvp(right->args[0], right->args);

         perror("execvp right");
         exit(1);
    }

    //pere

    close(fd[0]);
    close(fd[1]);

    wait(NULL);
    wait(NULL);

}