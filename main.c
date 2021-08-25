#include "shell.h"
#include <signal.h>

int get_inp(char *errormsg);
void prompt(int n);
int command(char **arguments, char **env, char *errormsg);


/**
 *main - Entry point
 *@argc: stores number of command-line arguments
 *@argv: array of character pointers listing all the arguments
 *
 *Return: Always 0
 */
int main(__attribute__ ((unused)) int argc, char **argv)
{
	int error = 1;
	char *errormsg;

	signal(SIGINT, SIG_IGN);
	errormsg = malloc(1024);
	if (!errormsg)
		return (1);
	while (error != 0)
	{
		error = get_inp(errormsg);
		if (abs(error) > 1)
		{
			printf("%s: ", argv[0]);
			printf("%d: ", abs(error) - 1);
			printf("%s", errormsg);
			printf("\n");
		}
		if (error < 0)
			error = 0;
	}
	free(errormsg);
	return (0);
}
/**
 *get_inp - function that get the input
 *@errormsg: will display an error message
 *
 *Return: a number, the error number
 */
int get_inp(char *errormsg)
{
	char *buffer;
	char **arguments, **times, **semicolons;
	int i, lines, semic, error, inte, characters;
	size_t buf_size = 1024;

	buffer = malloc(buf_size);
	if (!buffer)
		return (-1);
	inte = isatty(0);
	prompt(inte);
	if (inte)
		characters = getline(&buffer, &buf_size, stdin);
	else
		characters = read(0, buffer, buf_size);
	if (characters == -1)
	{
		free(buffer);
		return (0);
	}
	if (buffer[characters - 1] == '\n')
		buffer[characters - 1] = 0;
	if (buffer[0] == 0)
	{
		free(buffer);
		return (1);
	}
	times = str_to_arguments(buffer, '\n');
	free(buffer);
	for (lines = 0; times[lines]; lines++)
	{
		semicolons = str_to_arguments(times[lines], ';');
		free(times[lines]);
		for (semic = 0; semicolons[semic]; semic++)
		{
			arguments = str_to_arguments(semicolons[semic], ' ');
			free(semicolons[semic]);
			if (!arguments)
				return (-1);
			error = command(arguments, environ, errormsg);
			for (i = 0; arguments[i]; i++)
				free(arguments[i]);
			free(arguments);
		}
		free(semicolons);
	}
	free(times);
	return (inte ? error : (0 - error));
}
/**
 *command - funtion to parse the input string
 *@arguments: tokenized commands
 *@env: NULL terminated array of strings.
 *@errormsg:  will display an error message
 *
 *Return: always an integer
 */
int command(char **arguments, char **env, char *errormsg)
{
	int i, out;

	if (!arguments[0][0])
		return (1);
	i = search_bulit_in(arguments, env, errormsg);
	if (i != 0)
		return (i);
	i = search_command(arguments, env);
	if (i != 0)
		return (i);
	i = search_file(arguments, env);
	if (i != 0)
		return (i);
	out = mystrcpy(errormsg, arguments[0], 0);
	out += mystrcpy(errormsg, ": not found", out);
	return (2);
}
/**
 *prompt - function that will print the prompt
 *@n: defines interactive mode
 *
 *Return: nothing
 */
void prompt(int n)
{
	char cwd[201];
	int i;

	if (n)
	{
		getcwd(cwd, 256);
		for (i = 0; cwd[i]; i++)
			;
		set_col(4);
		write(1, cwd, i);
		set_col(1);
		write(1, "$ ", 2);
		set_col(0);
	}
}
