#ifndef PARSER_H
#define PARSER_H

#include "shell.h"

void parse_command(char *input, Command *cmd);
void reset_command(Command *cmd);

#endif