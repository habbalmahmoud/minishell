#include "../includes/minishell.h"
#include "../includes/execute.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>  // For debugging purposes

// Function to free a single environment node
void free_env_node(t_env *node) {
    if (node) {
        free(node->key);
        free(node->value);
        free(node);
    }
}

void exec_unset(t_exec_utils **util, char **args) {
	t_env **env = &(*util)->env;
    t_env *current;
    t_env *prev;
    int i;
    int found;

    // Assume success initially
    (*util)->code = 1;

    // Iterate over each argument in args
    for (i = 1; args[i] != NULL; i++) {
        found = 0;
        current = *env;
        prev = NULL;

        // Debugging output

        // Search for the environment variable to remove
        while (current != NULL) {
            // Debugging output

            if (!ft_strcmp(current->key, args[i])) {
                // Found the variable to unset
                found = 1;
                if (prev == NULL) {
                    // Removing the head of the list
                    *env = current->next;
                } else {
                    // Removing a non-head node
                    prev->next = current->next;
                }

                // Free the memory associated with the node
                free_env_node(current);

                // Debugging output

                // Break out of the while loop after deletion
                break;
            }
            prev = current;
            current = current->next;
        }

        // If variable was found and removed
        if (found) {
            (*util)->code = 0; // Set exit code to 0 to indicate success
        }
    }
}

// Function to free a single environment node

