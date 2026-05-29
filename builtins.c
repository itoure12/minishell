#include "builtins.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int is_builtin(Command *cmd) {
    
    if (cmd->args[0] == NULL) {
        return 0;
    }

    if(strcmp(cmd->args[0], "cd") == 0){
        return 1;
    }

    if(strcmp(cmd->args[0], "exit") == 0) {
        return 1;
    }

    if (strcmp(cmd->args[0], "help") == 0) {
        return 1;
    }

    return 0;
}

void execute_builtin(Command *cmd) {
    
   if(strcmp(cmd->args[0], "cd") == 0) {

      if(cmd->args[1] == NULL) {
        printf("cd: missing argument\n");
      } else {
        if (chdir(cmd->args[1]) != 0) {
            perror("cd");
        }
      }
   
   
    } else if(strcmp(cmd->args[0], "exit") == 0) {

        exit(0);
   
    } else if(strcmp(cmd->args[0], "help") == 0) {

        printf("Available built-in commands:\n");
        printf("  cd <path>   Change current directory\n");
        printf("  exit        Exit the shell\n");
        printf("  help        Show this help message\n");
        

    }




}