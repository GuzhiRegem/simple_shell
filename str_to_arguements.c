#include "shell.h"
/**
 *str_to_arguments - makes an array of strings from a string
 *@buffer: string to separate
 *@sep: separator
 *Return: array of strings
 */
char **str_to_arguments(char *buffer, char sep)
{
	char **out;
	int i, i2, i3, error = 0, arg_amount = 1, offs;
	char *ptr, *tmp;

	for (offs = 0; buffer[offs] == sep; offs++)
		;
	for (i = offs; buffer[i]; i++)
		if (buffer[i] == sep)
			if (buffer[i + 1] && (buffer[i + 1] != sep))
				arg_amount++;
	out = malloc((arg_amount + 1) * sizeof(char *));
	if (!out)
		return (out);
	out[arg_amount] = NULL;
	ptr = buffer + offs;
	for (i = 0; i < arg_amount; i++)
	{
		while (ptr[0] == sep)
			ptr = ptr + 1;
		for (i2 = 0; ptr[i2] && (ptr[i2] != sep); i2++)
			;
		tmp = malloc(i2 + 1);
		tmp[i2] = 0;
		if (!tmp)
		{
			error = 1;
			break;
		}
		for (i3 = 0; i3 < i2; i3++)
			tmp[i3] = ptr[i3];
		ptr += i2;
		out[i] = tmp;
	}
	if (error)
	{
		for (i2 = 0; i2 < i; i2++)
			free(out[i2]);
		free(out);
	}
	return (out);
}
/**
 *mystrcat - concatenate two strings
 *@a: string source
 *@b: string detination
 *
 *Return: modified strind dest
 */
char *mystrcat(char *a, char *b)
{
	char *p, *q, *rtn;

	rtn = q = malloc(strlen(a) + strlen(b) + 2);
	if (rtn)
	{
		for (p = a; (*q = *p) != '\0'; ++p, ++q)
			;
		*q = '/';
		++q;
		for (p = b; (*q = *p) != '\0'; ++p, ++q)
			;
	}
	return (rtn);
}
/**
 *get_env - function that gets the environ
 *@str: string pasing environ variable
 *
 *Return: always 0
 *
 */
char *get_env(char *str)
{
	int i, a, differ;

	for (i = 0; environ[i]; i++)
	{
		differ = 1;
		for (a = 0; str[a]; a++)
			if (str[a] != environ[i][a])
			{
				differ = 0;
				break;
			}
		if (differ)
			return (environ[i] + a + 1);
	}
	return (NULL);
}
/**
 *set_col - sets the color of the text from here on
 *@c: index of color
 *Return: nothing
 */
void set_col(int c)
{
	switch (c)
	{
	case 0:
		write(1, "\033[0;37m", 7);
		break;
	case 1:
		write(1, "\033[0;33m", 7);
		break;
	case 2:
		write(1, "\033[0;32m", 7);
		break;
	case 3:
		write(1, "\033[0;31m", 7);
		break;
	case 4:
		write(1, "\033[46;1m", 7);
		break;
	}
}
/**
 *mystrcpy - function copies the string pointed to by src
 *@dest:to the buffer pointed to by dest
 *@src: length of src
 *@offs: total of n bytes are written
 *
 *Return: a pointer to the destination string dest
 */
int mystrcpy(char *dest, const char *src, int offs)
{
	int i;
	char *tmp;

	tmp = dest + offs;
	for (i = 0; src[i] || (i >= 1024); i++)
		tmp[i] = src[i];
	tmp[i] = 0;
	return (i);
}
