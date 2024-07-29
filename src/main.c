/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 19:02:37 by nkanaan           #+#    #+#             */
/*   Updated: 2024/07/29 19:02:38 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	process_input(const char *input)
{ 
	if (input == NULL)
		return;
	if (ft_strcmp(input, "exit") == 0)
		exit(1);
	else if (ft_strncmp(input, "cd ", 3) == 0)
	{
		const char *path = input + 3;
		change_dir(path);
	}
	else if (ft_strcmp(input, "env") == 0)
	{
		char env[1024];
		if (getenv(env) == NULL)
			perror("getenv");
		else
			printf("%s\n", env);
	}
	else if (ft_strcmp(input, "pwd") == 0)
	{
		char cwd[1024];
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			perror("getcwd");
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
		input = readline(test);
       
		if (input == NULL) 
		{
			printf("\nExiting...\n");
			break;
		}

		add_history(input);
		process_input(input);

		free(input);
    }
}
