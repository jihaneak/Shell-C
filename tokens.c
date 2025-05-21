#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEL " "

void cell_split_line(char *line)
{
	char *tokens[6] = {0};
	int position;

	position = 0;
	for (char *token = strtok(line, DEL); token; token = strtok(NULL, DEL))
	{
		tokens[position++] = token;
	}

	position = 0;
	while (tokens[position])
		printf("%s\n", tokens[position++]);

}

int main(void)
{
	char s[] = "ls -la file.txt | cat";
	cell_split_line(s);

	return EXIT_SUCCESS;
}
