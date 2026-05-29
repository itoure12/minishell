#ifndef BUILTINS_H
#define BUILTINS_H

#include "shell.h"

int is_builtin(Command *cmd);
void execute_builtin(Command *cmd);

#endif