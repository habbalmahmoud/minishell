/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkanaan <nkanaan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 12:40:55 by nkanaan           #+#    #+#             */
/*   Updated: 2024/08/12 11:49:04 by nkanaan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "./minishell.h"
# include "./token.h"

/*/////////////////////////////////////////////////////////////
////////////		TYPES			    //////////
////////////////////////////////////////////////////////////*/
int	init_lexer(char *input, int id, t_lexer **lex, t_token **token);
int	l_tokenize(t_lexer *lex, t_token **token, int type, int *state);
/*/////////////////////////////////////////////////////////////
////////////		QUOTES			    //////////
////////////////////////////////////////////////////////////*/
void	l_state_handler_quote_in(t_lexer *lex, t_token **token, int type, int *state);
void	l_state_handler_quote_exit(t_lexer *lex, t_token **token, int type, int *state);
char	*l_remove_quotes(t_token *token);

/*/////////////////////////////////////////////////////////////
////////////		OPERATORS		    //////////
////////////////////////////////////////////////////////////*/
void	l_tokenize_ampersand(t_lexer *lex, t_token **token, int *state, int type);
void	l_handler_ampersand(t_lexer *lex, t_token **token, int type, int len);
void	l_tokenize_pipe(t_lexer *lex, t_token **token, int *state, int type);
void	l_handler_pipe(t_lexer *lex, t_token **token, int type, int len);
void	l_tokenize_next(t_lexer *lex, t_token **token, int type, int len);
void	l_tokenize_words(t_lexer *lex, t_token *token, int type);
int     handle_paren(t_lexer **lex, t_token **token, int *state, int type);

/*/////////////////////////////////////////////////////////////
////////////		GLOBBING		    //////////
////////////////////////////////////////////////////////////*/
char	**l_glob(const char *pattern, int *hits);
int	l_glob_match(const char *pattern, const char *string);
void	l_handler_wildcards(t_token *token, int count, char **glob_list);
size_t	l_glob_count(const char *pattern);


/*/////////////////////////////////////////////////////////////
////////////		LEXER_UTILS		    //////////
////////////////////////////////////////////////////////////*/
void    close_values(char *input, t_lexer **lexer);

#endif
