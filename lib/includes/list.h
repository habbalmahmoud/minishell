#ifndef LIST_H
# define LIST_H

# include "./libft.h"

typedef struct s_list
{
	void				*content;
	struct s_list		*next;
}	t_list;

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
int		ft_lstsize(t_list *lst);

#endif
