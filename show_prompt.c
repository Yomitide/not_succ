/**
 * main - Simple shell 0.1
 *
 * Description: A basic UNIX command line interpreter.
 *
 * Return: Always 0.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/* Function prototypes */
void display_prompt(void);
char *read_input(void);
void execute_command(char *command);

/**
 * main - Entry point of the shell.
 *
 * Return: Always 0.
 */
int main(void)
{
    char *command;

    while (1)
    {
        display_prompt();
        command = read_input();

        if (command == NULL)
        {
            printf("\n");
            break;
    }

        execute_command(command);
        free(command);
    }

    return 0;
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
    printf("$ ");
}

/**
 * read_input - Reads the user input from stdin.
 *
 * Return: Pointer to the input command string, or NULL on EOF.
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
 * execute_command - Executes the given command.
 *
 * @command: The command to execute.
 */
void execute_command(char *command)
{
    if (access(command, X_OK) == 0)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("Error: fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            char *args[2];
            args[0] = command;
            args[1] = NULL;
            if (execve(command, args, NULL) == -1)
            {
                perror("Error: execve failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            wait(NULL);
        }
    }
    else
    {
        printf("%s: command not found\n", command);
    }
}
