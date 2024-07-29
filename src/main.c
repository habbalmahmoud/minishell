#include "../includes/minishell.h"

void	process_input(const char *input)
{ 
	if (input == NULL)
		return;
	if (ft_strcmp(input, "exit") == 0)
		exit(1);
	else if (strncmp(input, "cd ", 3) == 0)
	{
		const char *path = input + 3;
		change_dir(path);
	}
	else if (strcmp(input, "pwd") == 0)
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror("getcwd");
		}
		else
			printf("%s\n", cwd);
        }
	else
		printf("Unknown command: %s\n", input);
    }

int	main()
{
	char	*input;

	while (1)
	{
		char	*dir = get_dir();
		char	*test = ft_strjoin(dir, "> ");
		printf("\033[0;36m");
		input = readline(test);
		printf("\033[0m");
        
		if (input == NULL) 
		{
			printf("\nExiting...\n");
			break;
		}

		add_history(input);
		process_input(input);
		printf("You entered: %s\n", input);

		free(input);
    }
}
