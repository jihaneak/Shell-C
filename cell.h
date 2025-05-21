#ifndef CELL_H
# define CELL_H


# include <unistd.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <sysexits.h>


#define Y		"\033[1;33m"
#define G		"\033[1;32m"
#define C 		"\033[1;36m"
#define RED		"\033[1;31m"
#define RST 	"\033[0m"

#define p(...)	printf(__VA_ARGS__)
#define ERROR(msg) fprintf(stderr, RED msg RST "\n")
#define SPACE	"\t\n\v\f\r "
#define CELL_JR	0


enum{
	OK,     
	ERROR   };

typedef struct s_builtin
{
    const char *builtin_name;
	int (*foo)(char **av);
} t_builtin;


int	cell_echo(char **args);  
int	cell_env(char **args);   
int	cell_exit(char **args);  

void 	dbzSpinnerLoading();  
void	printbanner(void);    


void	Chdir(const char *path);      
pid_t	Fork(void);                   
void	Execvp(const char *file, char *const argv[]); 
pid_t	Wait(int *status);
pid_t	Waitpid(pid_t pid, int *status, int options); 
void	*Malloc(size_t size);         
void	*Realloc(void *ptr, size_t size); char	*Getcwd(char *buf, size_t size); 
void	Getline(char **lineptr, size_t *n, FILE *stream); 
#endif
