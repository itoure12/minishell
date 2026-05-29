CC = gcc
CFLAGS = -Wall -Wextra

all: minishell

minishell: main.c shell.c parser.c builtins.c
	$(CC) $(CFLAGS) main.c shell.c parser.c builtins.c -o minishell

clean:
	rm -f minishell