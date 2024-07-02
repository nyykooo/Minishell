/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/01 17:59:55 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

void	analyze_input(t_minishell *shell);

// PARSING

// void	parsing_hub(char *input, t_minishell *shell);
// int	input_manager(char **input);
// t_token **token_manager(char *input);
// void	create_tokens(char **array, t_token ***tokens);
// char *check_meta(char *str);
// void	analyze_argument(t_token **tokens, t_minishell *shell);
// void	expand_dolar(t_arg *argument , t_minishell *shell);


// NEW PARSING

void	parsing_hub(t_minishell *shell);

// NEW PARSING - INPUT

void	input_manager(t_minishell *shell);
void	expand_pipes_redir(t_minishell *shell);

// NEW PARSING - TOKENS

void	tokenizer(t_minishell *shell);
void	token_creation(char **array, t_minishell *shell);
// void	analyze_tokens(t_arg **tokens, t_minishell *shell);
void	analyze_tokens(t_token *tokens, t_minishell *shell);
int		check_tokens(t_token *tokens);void	include_token(t_minishell *shell, char *argument, t_token *token);


// NEW PARSING - META

char	**check_pipe(char **tokens, t_minishell *shell);
char	**check_left_apend(char **tokens, t_minishell *shell);
char	**check_left_trunc(char **tokens, t_minishell *shell);
char	**check_right_apend(char **tokens, t_minishell *shell);
char	**check_right_trunc(char **tokens, t_minishell *shell);

// NEW PARSING - COMMANDS

void	create_command(t_token *tokens, t_minishell *shell);
void	include_arg(t_minishell *shell, char *input, t_arg *argument);

// NEW PARSING - ARGUMENTS

void	analyze_arguments(t_minishell *shell, t_cmd *cmd);

// NEW PARSING - QUOTES

void expand_quotes(t_token *argument, t_minishell *shell);
char *quote_del(char *input, t_minishell *shell);
int	skip_quotes(char *input, int *i);
int	skip_nquotes(char *input, int *i);
int		is_inside_quotes(char *str, size_t index);

// NEW PARSING - DOLLAR
void	expand_dolar(char **input , t_minishell *shell);
void	expand_tildes(char **input, t_minishell *shell);
void	expand_hashtag(char **input);

// FREE_ERROR_EXIT
void	free_shell(t_minishell *shell);
void	free_tokens(t_token *tokens);
void	free_array(char **array);
void	free_list(t_var *head);
void	free_var(t_var *head);
void	free_commands(t_cmd *commands);
char	*error_msg_construct(int nbr, ...);
int		put_error_msg(char *error_msg, int exit_status);

//ENVVAR_FTS

char	*create_envvar_content(char *name, char *value);
t_var	*find_envvar(t_var *envvar_list, char *name);
void	remove_envvar(t_var **envvar_list, t_var *envvar);
char	*get_value(t_var *envvar_list, char *name);
void	update_questionvar(t_minishell *shell);

// BUILTINS
void	handle_cd(t_cmd *command, t_minishell *shell);
void	handle_echo(t_cmd *command);
void	handle_equal(t_minishell *shell, t_cmd *command);
int		handle_export(t_minishell *shell);
void	handle_env(t_var *envvar_list, t_minishell *shell);
void	handle_unset(t_cmd *command, t_var **envvar_list);
void	handle_exec(t_minishell *shell, t_cmd *cmd);
void	handle_pwd(t_minishell *shell);
void	handle_exit(t_cmd *command, t_minishell *shell);

//ENVVAR_FTS
t_var	*find_envvar(t_var *envvar_list, char *name);
void	remove_envvar(t_var **envvar_list, t_var *envvar);
void	set_envvar(t_var **envvar_list, char *name, char *value, int flag);
char	*get_value(t_var *envvar_list, char *name);
char	**envvar_array(t_minishell *shell);
void	update_existing_envvar(t_var *envvar, char *name, char *value);

//TTY
void	edit_termios(void);

// VARIABLES
void	ft_varadd_back(t_var **lst, t_var *new);
t_var	*create_list(char **envp);

//SIGNALS
void	handle_sigint(int sig);


int	handle_pipe(t_cmd *commands);

#endif