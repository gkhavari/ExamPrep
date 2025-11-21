#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int starts_with(char *input, char *pattern)
{
	size_t i = 0;

	if (!input || !pattern)
		return (0);
	while (pattern[i] && input[i] && input[i] == pattern[i])
		i++;
	if (pattern[i] == '\0')
		return (1);
	return (0);
}

int main(int argc, char **argv)
{
	char *pattern = NULL;
	char *buffer = NULL;
	char *temp = NULL;
	char c = '\0';
	ssize_t n = 0;
	size_t buffersize = 0;
	size_t i = 0;
	size_t j = 0;

	if (argc != 2 || argv[1][0] == '\0')
		return (1);
	pattern = argv[1];
	while ((n = read(0, &c, 1))> 0)
	{
		if (i + 1 > buffersize)
		{
			if (buffersize == 0)
				buffersize = 64;
			else
				buffersize *= 2;
			temp = realloc(buffer, buffersize * sizeof(char));
			if (!temp)
			{
				free(buffer);
				perror("Error: realloc");
				return (1);
			}
			buffer = temp;
		}
		buffer[i] = c;
		i++;
	}
	if (n < 0)
	{
		free(buffer);
		perror("Error: read");
		return (1);
	}
	if (buffer)
		buffer[i] = '\0';
	else
	{
		perror("Error: something is wrong.");
		return (1);
	}
	i = 0;
	while (buffer[i])
	{
		if(starts_with(&buffer[i], pattern))
		{
			while(pattern[j])
			{
				write(1, "*", 1);
				j++;
				i++;
			}
			j = 0;
		}
		else
		{
			write(1, &buffer[i], 1);
			i++;
		}
	}
	free(buffer);
	return (0);
}
