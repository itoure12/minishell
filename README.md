# Mini Shell — Unix Shell Implementation in C

## Overview

Mini Shell is a lightweight Unix-like command-line interpreter written in C. It supports executing external programs, built-in commands, input/output redirection, and single-pipe command chaining. The project was developed to explore Linux systems programming concepts such as process creation, inter-process communication, file descriptors, and command parsing. It provides a simplified view of how traditional Unix shells operate internally.

---

## Features

- Execute external Linux commands using `fork()` and `execvp()`
- Built-in commands:
  - `cd` – change the current directory
  - `help` – display available commands
  - `exit` – terminate the shell
- Command parsing using `strtok()`
- Input redirection (`<`)
- Output redirection (`>`)
- Single-pipe command execution (`cmd1 | cmd2`)
- Process synchronization with `wait()`
- File descriptor management using `dup2()`
- Error handling with `perror()`
- Interactive shell prompt (`mysh$`)
- Memory-leak free implementation verified with Valgrind

---

## Architecture

### Project Structure

```text
minishell/
├── main.c          # Entry point of the program
├── shell.c         # Main shell loop, command execution, redirections, and pipes
├── shell.h         # Core constants, Command structure, and shell function declarations
├── parser.c        # Command parsing logic
├── parser.h        # Parser function declarations
├── builtins.c      # Built-in command implementation
├── builtins.h      # Built-in command declarations
└── Makefile        # Build automation
```

### How It Works

The program starts in `main.c`, which calls `shell_run()` to launch the interactive shell loop. The shell displays the `mysh$` prompt, reads user input with `fgets()`, and sends the input to `parse_command()`.

The parser breaks the input into tokens and fills a `Command` structure with arguments, redirection files, and pipe information. Then `shell_execute()` decides whether the command is a built-in command, a normal external command, or a piped command.

External commands are executed using `fork()` and `execvp()`, while the parent process waits with `wait()`. For redirections and pipes, the shell uses file descriptors, `dup2()`, and `pipe()` to connect command input and output correctly.

---

## Getting Started

### Prerequisites

- Linux or WSL (Windows Subsystem for Linux)
- GCC compiler
- Make
- Valgrind (optional, for memory leak detection)

### Installation

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/itoure12/minishell.git
cd minishell
```

### Build

Compile the project using Make:

```bash
make
```

### Run

Start the shell with:

```bash
./minishell
```

You should see the shell prompt:
mysh$

---

## Usage

### Execute External Commands

```bash
mysh$ ls
```

Output:
Makefile  builtins.c  builtins.h  main.c  minishell
parser.c  parser.h    shell.c     shell.h

### Display Current Directory

```bash
mysh$ pwd
```

Output:
/home/idriss/c_learning/minishell

### Built-in Help Command

```bash
mysh$ help
```

Output:
Available built-in commands:
cd <path>   Change current directory
exit        Exit the shell
help        Show this help message

### Output Redirection

```bash
mysh$ ls > output.txt
```

The command output is written to `output.txt` instead of the terminal.

### Input Redirection

```bash
mysh$ cat < test.txt
```

Output:
Hello from Mini Shell

### Pipe Commands

```bash
mysh$ ls | grep .c
```

Output:
builtins.c
main.c
parser.c
shell.c

The output of `ls` is redirected through a pipe and filtered by `grep`.

### Exit the Shell

```bash
mysh$ exit
```

The shell terminates and returns control to the operating system.

---

## Technical Details

### Process Creation

The shell executes external commands using the classic Unix `fork()` and `execvp()` model. A child process is created with `fork()`, allowing the shell itself to continue running independently. The child process then calls `execvp()` to replace its program image with the requested command, while the parent process waits for completion using `wait()`. This approach closely mirrors the behavior of traditional Unix shells.

### Pipes and Redirections

Input/output redirections and pipes are implemented using file descriptors and `dup2()`. For redirections, the shell opens the target file and redirects `stdin` or `stdout` to the corresponding file descriptor before executing the command. Pipes are created with `pipe()`, allowing the output of one process to become the input of another. This makes commands such as `ls | grep .c` possible by connecting two child processes through a communication channel.

### Memory Management

The project uses stack-allocated data structures and carefully manages all system resources. File descriptors are closed when no longer needed, and child processes are properly synchronized and terminated. The shell was tested with Valgrind and completed execution with no memory leaks and no reported memory errors, ensuring clean and reliable resource management.

---

## Author

**Idriss Toure**
Computer Engineering Student — University of Ottawa
Interested in systems programming, concurrency, and low-level software development
GitHub: [itoure12](https://github.com/itoure12)
LinkedIn: [Idriss Hamad Toure](https://www.linkedin.com/in/IdrissHamadToure)