
# Simple Shell

The `Simple Shell` project is a group project to create a simple UNIX command line interpreter. It involves designing and implementing a basic shell that can execute commands entered by the user. The project focuses on understanding the working principles of a shell and implementing the core functionalities.

![Cover Photo](shell.jpeg)

## Features
The `Simple Shell` supports the following features:

1. Execution of basic commands.
2. Handling of command lines with arguments.
3. Use of the `PATH` variable to find executables.
4. Built-in commands:
- `exit`: Exits the shell.
- `env`: Prints the current environment.
- `setenv`: Initializes or modifies an environment variable.
- `unsetenv`: Removes an environment variable.
- `cd`: Changes the current directory of the process.
5. Handling of command separators ;.
6. Handling of logical operators && and ||.
7. Implementation of aliases for commands.
8. Variables replacement, including $? and $$.
9. Support for comments using #.
10. Ability to read commands from a file.

## Getting Started
To compile the Simple Shell, use the following command:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

To run the shell in interactive mode, execute the compiled binary:

```
./hsh
```

To run the shell in non-interactive mode, you can provide a file as a command line argument:

```
./hsh script_file
```

## Usage Examples
Interactive mode:

```
$ ./hsh
```

```
($) /bin/ls
hsh main.c shell.c
($) exit
$
```

Non-interactive mode:

```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat script_file
/bin/ls
/bin/ls
$
$ cat script_file | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Advanced Features

The Simple Shell also implements the following advanced features:

`Simple shell 0.1.1`
- Implementation of a custom `getline` function.
- Use of a buffer to read multiple characters at once and minimize the number of `read` system calls.

`Simple shell 0.2.1`
- Use of custom parsing instead of strtok for handling command lines with arguments.

`Simple shell 0.4.1`
- Handling of arguments for the exit built-in command.

`setenv, unsetenv`
- Implementation of the `setenv` and `unsetenv` built-in commands for initializing, modifying, and removing environment variables.

`cd`
- Implementation of the cd built-in command for changing the current directory of the process.

`;`
- Handling of the command separator `;`to execute multiple commands sequentially.

`&& and ||`
- Handling of the logical operators `&&` and `||` to execute commands conditionally based on the success or failure of previous commands.

`alias`
- Implementation of the `alias` built-in command for defining and printing aliases for commands.

`Variables`
- Handling of variables replacement, including the special variables `$?` and `$$`.

`Comments`
- Handling of comments using `#`.

`File as input`
- Ability to read commands from a file as a command line argument.

## Authors
- [Ayomide Sufian](add your gitbub url)
- [Ifeanyi Kalu](htts://github.com/fazzy13)

©2023 ALX, All rights reserved.
