#include "shell.h"

/**
 *execute - execute the command
 *@command: array of stings.
 *@arguments: parsed string
 *@env: environment variable
 *
 *Return: nothing
 */

void execute(char *command, char **arguments, char **env)
{
	int pid, exit_status;

	pid = fork();
	if (pid == 0)
	{
		execve(command, arguments, env);
		exit(0);
	}
	else
		wait(&exit_status);
}

/**
 *execute_built_in - function will execute and works if biultin
 *@n: integer representing size
 *@arguments: tokenized commands
 *@env: NULL terminated array of strings
 *@errormsg: wrong, will display error
 *
 *Return: integer
 */

int execute_built_in(int n, char **arguments, char **env, char **errormsg)
{
	int i, out;

	switch (n)
	{
	case 0:
		i = cd(arguments[1]);
		if (!i)
		{
			out = mystrcpy(errormsg, "cd: ", 0);
			out += mystrcpy(errormsg, arguments[1], out);
			out += mystrcpy(errormsg, " not found.", out);
			return (2);
		}
		break;
	case 1:
		return (-1);
	}
	return (1);
}

/**
 *search_bulit_in - function checking 4 bultins
 *@arguments: tokenized commands
 *@env: NULL terminated array of strings
 *@errormsg:  will display an error message
 *
 *Return: 0
 */

int search_bulit_in(char **arguments, char **env, char **errormsg)
{
	int i;
	char *commands[] = {"cd",
			    "exit",
			    "history",
			    "help",
			    NULL};
	for (i = 0; commands[i]; i++)
		if (strcmp(commands[i], arguments[0]) == 0)
		{
			return (execute_built_in(i, arguments, env, errormsg));
		}
	return (0);
}

/**
 *search_command - function that look up for a command
 *@arguments: tokenized commands
 *@env: NULL terminated array of strings
 *
 *Return: integer founded, if fails 0
 */


int search_command(char **arguments, char **env)
{
	char *path, *command, *first_arg;
	struct stat statbuf;
	char **paths;
	int i, found = 0, file;

	path = get_env("PATH");
	paths = str_to_arguments(path, ':');
	if (!paths)
		return (0);
	for (i = 0; paths[i] && !found; i++)
	{
		command = mystrcat(paths[i], arguments[0]);
		if (command)
		{
			file = stat(command, &statbuf);
			if (file == 0)
			{
				execute(command, arguments, env);
				found = 1;
			}
		}
		free(command);
	}
	for (i = 0; paths[i]; i++)
		free(paths[i]);
	free(paths);
	return (found);
}

/**
 *search_file - function that looks for a file
 *@arguments: tokenized commands
 *@env: NULL terminated array of strings
 *
 *Return: if file exists 1, if not 0
 */

int search_file(char **arguments, char **env)
{
	int file;
	struct stat statbuf;

	file = stat(arguments[0], &statbuf);
	if (file == 0)
	{
		execute(arguments[0], arguments, env);
		return (1);
	}
	return (0);
}
