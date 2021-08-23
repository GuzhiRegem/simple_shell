#include "shell.h"

/**
 *cd - change working directory
 *@dir: directory to go
 *Return: error code
 */
int cd(char *dir)
{
	int file;
	struct stat statbuf;

	if (!dir)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	file = stat(dir, &statbuf);
	if (file == -1)
		return (0);
	chdir(dir);
	return (1);
}
