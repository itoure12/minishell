#include "parser.h"
#include <string.h>
#include <stdlib.h>

void reset_command(Command *cmd) {
    cmd->argc = 0;

    cmd->input_file = NULL;

    cmd->output_file = NULL;

    cmd->pipe_count = 0;

    for (int i = 0; i< MAX_ARGS; i++) {
        cmd->args[i] = NULL;
    }
    
}

void parse_command(char *input, Command *cmd) {
    reset_command(cmd);

    char *token = strtok(input, " \t\n");

    while(token != NULL){

        if(strcmp(token,">") == 0){
            token = strtok(NULL, " \t\n");
            cmd->output_file = token;
       
       
        } else if (strcmp(token, "<") == 0){
            token = strtok(NULL, " \t\n");
            cmd->input_file = token;
        
        
        } else if(strcmp(token, "|") == 0) {
            cmd->pipe_count++;

           if (cmd->argc < MAX_ARGS - 1) {
              cmd->args[cmd->argc] = token;
              cmd->argc++;
           }
        
        
        } else {
            if(cmd->argc < MAX_ARGS -1) {
               cmd->args[cmd->argc] = token;
               cmd->argc++;
            }
        }

        token = strtok(NULL, " \t\n");
    }

    cmd->args[cmd->argc]= NULL;


}
