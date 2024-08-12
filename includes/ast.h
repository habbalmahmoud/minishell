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

/**
 *
	<command line>	::= 	<job> ';' <command line>
						|	<job> ';'
						| 	<job> '&' <command line>
						|	<job> '&'
							<job>

	<job>			::=		<command> '|' <job>
						|	<command>

	<command>		::=		<simple command> '<' <filename>
						|	<simple command> '>' <filename>
						|	<simple command>

	<simple command>::=		<pathname> <token list>

	<token list>	::=		<token> <token list>
						|	(EMPTY)

 *
 *
 *
**/

struct s_tree;

typedef enum ast_type
{
	AST_REDIRECT_IN,
	AST_REDIRECT_OUT,
	AST_HEREDOC,
	AST_APPEND,
}	e_ast_type;

/* typedef union	ast_unions
{
	struct AST_SIMPLECMD
	{
		struct s_tree *right;
		struct s_tree *left;
	}	AST_SIMPLECMD;
	struct AST_REDIRECT_IN
	{
		AST_SIMPLECMD;
	}	AST_REDIRECT_IN;
	struct AST_REDIRECT_OUT 
	{
		AST_SIMPLECMD;
	}	AST_REDIRECT_IN;
	struct AST_APPEND 
	{
		struct s_tree *right; struct s_tree *left;
	}	AST_REDIRECT_IN;
	struct AST_HEREDOC 
	{
		struct s_tree *right; struct s_tree *left;
	}	AST_REDIRECT_IN;
}	u_ast_unions;
*/

typedef struct s_leaf
{
	char	**value;
	e_ast_type type;
}	t_leaf;

typedef struct s_tree
{
	t_leaf	*root;
	t_leaf	*left;
	t_leaf	*right;
}	t_tree;

void	init_parser(t_lexer **lexer);
void	p_build_tree(t_token *token, t_tree *ast);

#endif
