
#include "cell.h"


int	status = 0;


t_builtin	g_builtin[] = 
{
	{.builtin_name = "echo", .foo=cell_echo},   /* Echo text to stdout */
	{.builtin_name = "env", .foo=cell_env},     /* Print environment */
	{.builtin_name = "exit", .foo=cell_exit},  /* Exit the shell */
	{.builtin_name = NULL},                    /* Sentinel */
};


void	cell_launch(char **args)
{

		if (Fork() == CELL_JR)
	{
		
		Execvp(args[0], args);
	}
	else
	{
				Wait(&status);

	}
}

void	cell_execute(char **args)
{
	int			i;
	const char	*curr_builtin;

	if (!args || !args[0])
		return ;
	i = 0;

		while ((curr_builtin = g_builtin[i].builtin_name))
	{
		if (!strcmp(args[0], curr_builtin))
		{
			
			if ((status = (g_builtin[i].foo)(args)))
				p("%s failed\n", curr_builtin);
			return ;
		}
		i++;
	}
	
	 
	cell_launch(args);
}

char	*cell_read_line(void)
{
	char	*line;
	size_t	bufsize;
	char	cwd[BUFSIZ];

	line = NULL;
	bufsize = 0;
	
	if (isatty(fileno(stdin)))
	{
		if (status)
			p("🥭"C"[%s]"RED"[%d]"RST"🥭 > ", 
					Getcwd(cwd, BUFSIZ), 
					status);
		else
			p("🥭"C"[%s]"RST"🥭 > ", 
					Getcwd(cwd, BUFSIZ));
	}

	Getline(&line, &bufsize, stdin);
	return (line);
}



char	**cell_split_line(char *line)
{
	size_t			bufsize;
	unsigned long	position;
	char			**tokens;

	bufsize = BUFSIZ;
	position = 0;
	tokens = Malloc(bufsize * sizeof *tokens);

	for (char *token = strtok(line, SPACE); token; token = strtok(NULL, SPACE))
	{
		tokens[position++] = token;	
		if (position >= bufsize)
		{
			bufsize *= 2;
			tokens = Realloc(tokens, bufsize * sizeof *tokens);
		}
	}
	tokens[position] = NULL;
	return (tokens);
}


int	main()
{
	
	
	char	*line;
	char	**args;

		while ((line = cell_read_line()))
	{

		
		args = cell_split_line(line);	

		
		if (args[0] && !strcmp(args[0], "cd"))
			Chdir(args[1]);
		
		
		cell_execute(args);

		
		free(line);
		free(args);
	

	}

	return (EXIT_SUCCESS);
}
