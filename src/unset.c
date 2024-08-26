#include "../includes/minishell.h"
#include "../includes/execute.h"


void exec_unset(t_env **env, t_exec_utils *util, char **name)
{
    t_env *head; 
    t_env *prev;

    head = (*env);
    prev = NULL;
    while (head)
    {
        if (!ft_strcmp(head->key, name[1]))
        {
            if (prev == NULL)
                *env = head->next;
            else
                prev->next = head->next;

            free(head->key);
            free(head->value);
            free(head);

	    util->code = 0;
            return;
        }
        prev = head;
        head = head->next;
    }
}
