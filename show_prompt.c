/**
 * main - Simple shell 0.4
 *
 * Description: A basic UNIX command line interpreter.
 *
 * Return: Always 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define BUFFER_SIZE 1024
#define TOKEN_DELIM " \t\r\n\a"

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
char **split_arguments(char *line);
char *find_command_path(char *command);
void execute_command(char **args);
void print_environment(void);

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *line;
    char **args;

    while (1)
    {
        display_prompt();
        line = read_input();

        if (line == NULL)
        {
            printf("\n");
            break;
        }

        args = split_arguments(line);
        if (args == NULL)
        {
            free(line);
            continue;
        }

        if (strcmp(args[0], "exit") == 0)
        {
            free(line);
            free(args);
            break;
        }
        else if (strcmp(args[0], "env") == 0)
        {
            print_environment();
        }
        else
        {
            execute_command(args);
        }

        free(line);
        free(args);
    }

    return 0;
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
    printf(":) ");
}

/**
 * read_input - Reads the user input from stdin.
 *
 * Return: Pointer to the input line string, or NULL on EOF.
 */
char *read_input(void)
{
    char *buffer;
    size_t buffer_size = BUFFER_SIZE;
    ssize_t read_bytes;

    buffer = (char *)malloc(sizeof(char) * buffer_size);
    if (!buffer)
    {
        perror("Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    read_bytes = getline(&buffer, &buffer_size, stdin);

    if (read_bytes == -1)
    {
        if (feof(stdin))
            return NULL;

        perror("Error: getline failed");
        exit(EXIT_FAILURE);
    }

    buffer[read_bytes - 1] = '\0';

    return buffer;
}

/**
 * split_arguments - Splits the line into an array of arguments.
 *
 * @line: The input line string.
 *
 * Return: Array of arguments, or NULL on failure.
 */
char **split_arguments(char *line)
{
    int buffer_size = BUFFER_SIZE;
    int position = 0;
    char **arguments = malloc(buffer_size * sizeof(char *));
    char *token;

    if (!arguments)
    {
        perror("Error: malloc failed");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, TOKEN_DELIM);
    while (token != NULL)
    {
        arguments[position] = token;
        position++;

        if (position >= buffer_size)
        {
            buffer_size += BUFFER_SIZE;
            arguments = realloc(arguments, buffer_size * sizeof(char *));
            if (!arguments)
            {
                perror("Error: realloc failed");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, TOKEN_DELIM);
    }
    arguments[position] = NULL;

    return arguments;
}

/**
 * find_command_path - Finds the full path of the command.
 *
 * @command: The command.
 *
 * Return: Full path of the command, or NULL if not found.
 */
char *find_command_path(char *command)
{
    char *path = getenv("PATH");
    char *dir;
    char *path_copy = strdup(path);
    char *token;

    if (!path_copy)
    {
        perror("Error: strdup failed");
        exit(EXIT_FAILURE);
    }

    token = strtok(path_copy, ":");
    while (token != NULL)
    {
        dir = malloc(strlen(token) + strlen(command) + 2);
        if (!dir)
        {
            perror("Error: malloc failed");
            exit(EXIT_FAILURE);
        }
        sprintf(dir, "%s/%s", token, command);
        if (access(dir, X_OK) == 0)
        {
            free(path_copy);
            return dir;
        }
        free(dir);
        token = strtok(NULL, ":");
    }

    free(path_copy);
    return NULL;
}

/**
 * execute_command - Executes the given command with arguments.
 *
 * @args: Array of command and arguments.
 */
void execute_command(char **args)
{
    char *command_path = find_command_path(args[0]);

    if (command_path != NULL)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Error: fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            if (execve(command_path, args, NULL) == -1)
            {
                perror("Error: execve failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }

        free(command_path);
    }
    else
    {
        printf("%s: command not found\n", args[0]);
    }
}

/**
 * print_environment - Prints the current environment variables.
 */
void print_environment(void)
{
    extern char **environ;

    int i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
}

