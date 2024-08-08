#ifndef LIST_H
# define LIST_H


# include <unistd.h>
# include <stdlib.h>
# include "../../includes/token.h"

t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(int content);
void	ft_lstadd_back(t_list **lst, t_list *new_n);
void	ft_lstadd_front(t_list **lst, t_list *new_n);
void	ft_lstdelone(t_list *lst);
int		ft_lstsize(t_list *lst);
void	ft_lstclear(t_list **lst);

#endif
