/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:10:49 by nkanaan           #+#    #+#             */
/*   Updated: 2024/09/08 17:09:28 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../includes/minishell.h"
#include "../../../../includes/lexer.h"
#include "../../../../includes/token.h"
#include "../../../../includes/execute.h"

typedef struct s_expand
{
	t_node		*list_head;
	t_node		*last_node;
	char		*start;
	char		*pid;
	char		*exit_code;
	char		*var_start;
	size_t		len;
	char		*var_name;
	char		*env_value;
	char		*text_start;
	size_t		text_len;
	char		*text;
	size_t		total_len;
	t_node		*curr;
	char		*res;
	char		*ptr;
	size_t		data_len;
}	t_expand;

char	*get_env_value(const char *key, t_env *env);

t_node	*append_node(t_node *head, char *data)
{
	t_node	*new_node;
	t_node	*current;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->data = ft_strdup(data);
	if (!new_node->data)
	{
		free(new_node);
		return (NULL);
	}
	new_node->next = NULL;
	if (!head)
		return (new_node);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (head);
}

void	free_list(t_node *head)
{
	t_node	*current;
	t_node	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
}

void	expand_helper(t_expand *ex, t_env *env)
{
	ex->text_start = ex->start;
	while (*ex->start && *ex->start != '$')
		ex->start++;
	ex->text_len = ex->start - ex->text_start;
	ex->text = strndup(ex->text_start, ex->text_len);
	if (ex->text)
	{
		if (ex->list_head)
			ex->last_node = append_node(ex->last_node, ex->text);
		else
		{
			ex->last_node = append_node(NULL, ex->text);
			ex->list_head = ex->last_node;
		}
		free(ex->text);
	}
}

void	expand_exit_code(t_expand *ex, t_env *env)
{
	ex->start++;
	ex->exit_code = get_env_value("?", env);
	if (ex->exit_code)
	{
		ex->list_head = append_node(ex->list_head, ex->exit_code);
		ex->last_node = ex->list_head;
	}
}

void	expand_var(t_expand *ex, t_env *env)
{
	ex->var_start = ex->start;
	while (*ex->start && (ft_isalnum(*ex->start)
			|| *ex->start == '_'))
		ex->start++;
	ex->len = ex->start - ex->var_start;
	if (ex->len > 0)
	{
		ex->var_name = strndup(ex->var_start, ex->len);
		if (ex->var_name)
		{
			ex->env_value = get_env_value(ex->var_name, env);
			free(ex->var_name);
			if (ex->env_value && ft_strlen(ex->env_value) > 0)
			{
				ex->list_head = append_node(ex->list_head,
						ex->env_value);
				ex->last_node = ex->list_head;
			}
			free(ex->env_value);
		}
	}
}

void	expand_single(t_expand *ex, t_env *env)
{
	if (*ex->start == '\0' || *ex->start == ' ')
	{
		ex->list_head = append_node(ex->list_head, "$");
		ex->last_node = ex->list_head;
	}
	if (*ex->start == '$')
	{
		ex->start++;
		ex->pid = get_env_value("$", env);
		if (ex->pid)
		{
			ex->list_head = append_node(ex->list_head, ex->pid);
			ex->last_node = ex->list_head;
		}
	}
	if (*ex->start == '?')
		expand_exit_code(ex, env);
	else
		expand_var(ex, env);
}

int		finalize_expansion(t_expand *ex, t_env *env)
{
	ex->total_len = 0;
	ex->curr = ex->list_head;
	while (ex->curr)
	{
		ex->total_len += ft_strlen(ex->curr->data);
		ex->curr = ex->curr->next;
	}
	ex->res = malloc(ex->total_len + 1);
	if (!ex->res)
	{
		free_list(ex->list_head);
		return (1);
	}
	ex->ptr = ex->res;
	ex->curr = ex->list_head;
	while (ex->curr)
	{
		ex->data_len = ft_strlen(ex->curr->data);
		ft_memcpy(ex->ptr, ex->curr->data, ex->data_len);
		ex->ptr += ex->data_len;
		ex->curr = ex->curr->next;
	}
	return (0);
}

char	*expand_variables(char *value, int exp, t_env *env)
{
	t_expand	*ex;

	ex = ft_calloc(1, sizeof(t_expand));
	if (!exp)
		return (ft_strdup(value));
	ex->list_head = NULL;
	ex->last_node = NULL;
	ex->start = value;
	while (*ex->start)
	{
		if (*ex->start == '$')
		{
			ex->start++;
			expand_single(ex, env);
		}
		else
			expand_helper(ex, env);
	}
	if (!ex->list_head)
		return (ft_strdup(""));
	if (finalize_expansion(ex, env) == 1)
		return (NULL);
	*ex->ptr = '\0';
	free_list(ex->list_head);
	return (ex->res);
}

char	*get_env_value(const char *key, t_env *env)
{
	t_env	*head;

	head = env;
	while (head)
	{
		if (ft_strcmp(key, head->key) == 0)
			return (ft_strdup(head->value));
		head = head->next;
	}
	return (NULL);
}
