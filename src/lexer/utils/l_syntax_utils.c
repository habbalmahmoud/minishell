#include "../../../includes/lexer.h"
#include "../../../includes/execute.h"

int	post_pipe(t_token *temp, t_exec_utils **utils)
{
	if (temp->type != TYPE_WORD && (temp->next->next->type != TYPE_LSHIFT
			|| temp->next->next->type != TYPE_RSHIFT
			|| temp->next->next->type != TYPE_WORD
			|| temp->next->next->type != TYPE_HEREDOC
			|| temp->next->next->type != TYPE_APPEND))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putendl_fd("\'", 2);
		(*utils)->code = 2;
		return (0);
	}
	return (1);
}

int	post_redir(t_token *temp, t_exec_utils **utils)
{
	if ((temp->type != TYPE_WORD || temp->type != TYPE_PIPE)
		&& temp->next->next->type != TYPE_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putendl_fd("\'", 2);
		(*utils)->code = 2;
		return (0);
	}
	return (1);
}

int	post_and_or(t_token *temp, t_exec_utils **utils)
{
	if (temp->type != TYPE_WORD && temp->next->next->type != TYPE_WORD)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token", 2);
		ft_putstr_fd(" `", 2);
		ft_putstr_fd(temp->value, 2);
		ft_putendl_fd("\'", 2);
		(*utils)->code = 2;
		return (0);
	}
	return (1);
}
