/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/09 14:43:19 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FUNCTIONC_H
# define FUNCTIONC_H

#include "structures.h"

void	analyze_input(t_minishell *shell);


// PARSING

t_token **parsing_hub(char *input);
int	input_manager(char **input);
t_token **token_manager(char *input);
void	create_tokens(char **array, t_token ***tokens);
char *check_meta(char *str);
void	analyze_argument(t_token **tokens);


// FREE_ERROR_EXIT
void	free_shell(t_minishell *shell);
void	free_tokens(t_token **tokens);
void	free_array(char **array);
void	free_list(t_var *head);
void	handle_exit(t_minishell *shell);
void	free_var(t_var *head);


// BUILTINS
void	handle_cd(t_token **tokens, t_minishell *shell);
void	handle_echo(t_token **tokens);
void	handle_equal(t_minishell *shell, t_token *token);

//ENVVAR_FTS
t_var	*find_envvar(t_var *envvar_list, char *name);
void	remove_envvar(t_var **envvar_list, t_var *envvar);
void	set_envvar(t_var **envvar_list, char *name, char *value);
char	*get_value(t_var *envvar_list, char *name);

//TTY
void	edit_termios(void);





// VARIABLES

void ft_varadd_back(t_var **lst, t_var *new_node);
t_var *create_list(char **envp);

#endif