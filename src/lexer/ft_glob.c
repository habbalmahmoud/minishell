/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_glob.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:42:56 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/01 15:42:57 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/lexer.h"
# include <dirent.h>
// Match function: returns 1 if string matches the pattern, 0 otherwise
static int match(const char *pattern, const char *string) {
    while (*pattern) {
        if (*pattern == '*') {
            pattern++;
            if (!*pattern) return 1;
            while (*string) {
                if (match(pattern, string)) return 1;
                string++;
            }
            return 0;
        } else if (*pattern == '?') {
            if (!*string) return 0;
            pattern++;
            string++;
        } else {
            if (*pattern != *string) return 0;
            pattern++;
            string++;
        }
    }
    return *string == '\0';
}

// Glob function: returns a list of matched filenames
char **ft_glob(const char *pattern, int *num_matches) {
    DIR *dir;
    struct dirent *entry;
    char **matches = NULL;
    int count = 0;

    // Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    // Read directory entries
    while ((entry = readdir(dir)) != NULL) {
        if (match(pattern, entry->d_name)) {
            matches = realloc(matches, sizeof(char *) * (count + 1));
            if (matches == NULL) {
                perror("realloc");
                closedir(dir);
                return NULL;
            }
            matches[count] = malloc(strlen(entry->d_name) + 1);
            if (matches[count] == NULL) {
                perror("malloc");
                closedir(dir);
                return NULL;
            }
            strcpy(matches[count], entry->d_name);
            count++;
        }
    }

    closedir(dir);

    *num_matches = count;
    return matches;
}


