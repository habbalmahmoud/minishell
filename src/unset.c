#include "../includes/minishell.h"
#include "../includes/execute.h"

void print_env_list(t_env *list) {
    while (list) {
        printf("%s=%s\n", list->key, list->value);
        list = list->next;
    }
}
void free_env_node(t_env *node) {
    if (node) {
        free(node->key);
        free(node->value);
        free(node);
    }
}

void delete_env_node(t_env **env_list, const char *key) {
    if (env_list == NULL || *env_list == NULL) return;

    t_env *current = *env_list;
    t_env *prev = NULL;

    // If the node to be deleted is the first node
    if (current != NULL && strcmp(current->key, key) == 0) {
        *env_list = current->next; // Change head
        free_env_node(current); // Free old head
        return;
    }

    // Search for the key to be deleted
    while (current != NULL && strcmp(current->key, key) != 0) {
        prev = current;
        current = current->next;
    }

    // If the key was not found
    if (current == NULL) return;

    // Unlink the node from the list
    prev->next = current->next;

    // Free memory
    free_env_node(current);
}

void	internal_unset(t_env **env, char *key)
{
	if (env == NULL || key == NULL)
		return ;
	delete_env_node(env, key);
}

void	exec_unset(t_env **env_list, char **keys) {
    if (env_list == NULL || keys == NULL) return;

    for (int i = 0; keys[i] != NULL; i++) {
        delete_env_node(env_list, keys[i]);
    }
	//printf("POST UNSET:\n");
	//print_env_list((*env_list));
}

