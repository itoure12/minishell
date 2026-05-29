#ifndef SHELL_H
#define SHELL_H

#define MAX_INPUT 1024
#define MAX_ARGS 64
#define MAX_PATH 256
typedef struct {
    char *args[MAX_ARGS];
    int argc;
    char *input_file;
    char *output_file;
    int pipe_count;
} Command;

void shell_run(void);
void shell_execute(Command *cmd);
void shell_execute_pipe(Command *left, Command *right);

#endif
