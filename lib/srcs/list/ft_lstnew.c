/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:26:33 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/29 20:34:31 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

t_lex_ll	*l_lstnew(int id)
{
	t_lex_ll	*node;

	node = malloc(sizeof(t_lex_ll));
	if (!node)
		return (NULL);
	node->id = id;
	node->next = NULL;
	node->lexer = NULL;
	return (node);
}

t_env *env_lstnew(const char *key, const char *value) {
    t_env *new = malloc(sizeof(t_env));
    if (new == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    new->key = strdup(key); // Duplicate key
	if (!value)
		new->value = ft_strdup("");
	else
		new->value = strdup(value); // Duplicate value
    new->next = NULL;
    return new;
}
