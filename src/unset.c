#include "../includes/minishell.h"
#include "../includes/execute.h"
/*
void	exec_unset(t_exec_utils **util, char **args)
{
	t_env	**env;
	t_env	*store;
	t_env	*head;

	env = &(*util)->env;
	head = (*env);
	store = head->next;
		while (head)
		{
			if (!ft_strcmp(args[1], head->key))
			{
				free(head->key);
				free(head->value);
				free(head);
			}
			head->next = store;
			head = head->next;
		}
} */

// Function to free a single node
void free_node(t_env *node) {
    if (node) {
        free(node->key);
        free(node->value);
        free(node);
    }
}


void exec_unset(t_exec_utils **util, char **keys_to_delete) {
    if (!util || !*util || !(*util)->env || !keys_to_delete) {
        return;
    }

    t_env *current = (*util)->env;
    t_env *prev = NULL;

    while (current != NULL) {
        int match_found = 0;

        // Check if the current node's key matches any key in the array
        for (size_t i = 0; keys_to_delete[i]; i++) {
            if (strcmp(current->key, keys_to_delete[i]) == 0) {
                match_found = 1;
                break;
            }
        }

        if (match_found) {
            // Node to delete
            if (prev) {
                // Node to delete is not the head
                prev->next = current->next;
            } else {
                // Deleting the head node
                (*util)->env = current->next;
            }
            t_env *node_to_delete = current;
            current = current->next;  // Move to next node before freeing the current one
            free_node(node_to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
}


// Function to delete nodes with matching keys

