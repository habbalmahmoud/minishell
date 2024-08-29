#include "../includes/minishell.h"
#include "../includes/execute.h"

void remove_nodes(t_exec_utils *utils, const char *key) {
    
    t_env *current = utils->env;
    if (!current || !key) {
        return;
    }

    t_env *prev = NULL;
    if (current && strcmp(current->key, key) == 0) {
        utils->env = current->next;
        free(current->key);
        free(current->value);
       
        
        return;
    }
    while (current && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    if (!current) {
        return;
    }
    if (prev) {
        prev->next = current->next;
    }
    free(current->key);
    free(current->value);
    free(current);
}

void    exec_unset(t_exec_utils *utils, char **keys)
{
    int i;

    i = 1;
    while(keys[i])
    {
        remove_nodes(utils, keys[i]);
        i++;
    }
}
