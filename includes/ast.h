#ifndef AST_H
# define AST_H
# include "./minishell.h"

//////////////////// AST TEMPLATE ///////////////////////
/*
                 __ PIPE__
                     ___/              \____
                    /                       \
            COMMAND                    __ PIPE _
          /        \                  /         \
    ARGUMENTS   REDIRECTIONS	    CMD        _ CMD__
        |          |     |           |           /    \
       cat        <<     >       ARGUMENTS    ARGUMENTS	    REDIR
                   |     |         |   |      |   |   |        |
                 "..."  file      wc  -c      tr  -d " "       >
                                                               |
                                                             file2
*/

typedef enum e_ast_type
{
	GENERAL,
	SIMPLECOMMAND,
	REDIRECTIN,
}	t_ast_type;

typedef struct s_leaf
{
	char	**value;
	t_ast_type type;
}	t_leaf;

typedef struct s_tree
{
	t_leaf	*root;
	t_leaf	*left;
	t_leaf	*right;
}	t_tree;

void	init_parser(t_lexer **lexer);

#endif
