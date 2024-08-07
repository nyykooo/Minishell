/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 13:06:24 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

# define HRDC_EOF "-minishell: Warning: \
here-document delimited by end-of-file\n"

t_minishell	*ft_get_shell(void);

void		ft_analyze_input(t_minishell *shell);

// PARSING

// void	parsing_hub(char *input, t_minishell *shell);
// int	input_manager(char **input);
// t_token **token_manager(char *input);
// void	create_tokens(char **array, t_token ***tokens);
// char *check_meta(char *str);
// void	analyze_argument(t_token **tokens, t_minishell *shell);
// void	expand_dolar(t_arg *argument , t_minishell *shell);

// NEW PARSING

void		parsing_hub(t_minishell *shell);

// NEW PARSING - INPUT

int			input_manager(t_minishell *shell);
void		expand_pipes_redir(t_minishell *shell);

// NEW PARSING - TOKENS

void		tokenizer(t_minishell *shell);
void		token_creation(char **array, t_minishell *shell);
// void	analyze_tokens(t_arg **tokens, t_minishell *shell);
void		analyze_tokens(t_token *tokens, t_minishell *shell);
int			check_tokens(t_token *tokens);
void		include_token(t_minishell *shell, char *argument, t_token *token);

// NEW PARSING - META

char		**check_pipe(char **tokens, t_minishell *shell);
char		**check_left_apend(char **tokens, t_minishell *shell);
char		**check_left_trunc(char **tokens, t_minishell *shell);
char		**check_right_apend(char **tokens, t_minishell *shell);
char		**check_right_trunc(char **tokens, t_minishell *shell);

// NEW PARSING - COMMANDS

void		create_command(t_token *tokens, t_minishell *shell);
void		include_arg(t_minishell *shell, char *input, t_arg *argument);

// NEW PARSING - ARGUMENTS

void		analyze_arguments(t_minishell *shell, t_cmd *cmd);

// NEW PARSING - QUOTES

void		expand_quotes(t_token *argument, t_minishell *shell);
char		*quote_del(char *input, t_minishell *shell);
int			skip_quotes(char *input, int *i);
int			skip_nquotes(char *input, int *i);
int			ft_is_inside_quotes(char *str, size_t index);

// NEW PARSING - EQUAL

bool		ft_check_equal(t_token *token);

// NEW PARSING - DOLLAR

void		expand_dolar(char **input, t_minishell *shell);
void		expand_tildes(char **input, t_minishell *shell);
void		expand_hashtag(char **input);

// FREE_ERROR_EXIT

void		free_shell(t_minishell *shell);
void		free_tokens(t_token *tokens);
void		free_array(char **array);
void		free_list(t_var *head);
void		free_var(t_var *head);
void		free_commands(t_cmd *commands);
char		*error_msg_construct(int nbr, ...);
int			put_error_msg(char *error_msg, int exit_status);
void		ft_analyze_cmd(t_cmd *command);
void		ft_print_error(t_minishell *shell, bool must_free, \
int exit_status, int nbr, ...);

//ENVVAR_FTS
char		*ft_create_envvar_content(char *name, char *value);
char		*ft_get_value(t_var *envvar_list, char *name);
void		update_vars(t_minishell *shell);
void		ft_add_new_envvar(t_var **envvar_list, char *name, \
char *value, int flag);
void		ft_update_underlinevar(t_minishell *shell);
void		ft_set_underline(t_var **envvar);
void		ft_update_questionvar(t_minishell *shell);
void		ft_create_questionvar(t_var **envvar);

//ENVVAR_FTS
t_var		*ft_find_envvar(t_var *envvar_list, char *name);
void		ft_remove_envvar(t_var **envvar_list, t_var *envvar);
void		ft_set_envvar(t_var **envvar_list, char *name, \
char *value, int flag);
char		**envvar_array(t_minishell *shell);
void		ft_update_existing_envvar(t_var *envvar, char *name, char *value);

// BUILTINS
void		handle_cd(t_cmd *command, t_minishell *shell);
void		handle_echo(t_cmd *command);
void		ft_handle_equal(t_minishell *shell, t_cmd *command);
int			handle_export(t_minishell *shell);
void		handle_env(t_var *envvar_list, t_minishell *shell, t_cmd *command);
void		handle_unset(t_cmd *command, t_var **envvar_list);
void		ft_handle_exec(t_minishell *shell, t_cmd *cmd);
void		handle_pwd(t_minishell *shell);
void		handle_exit(t_cmd *command, t_minishell *shell);

// EXPORT
void		ft_print_export(t_var *current);
void		ft_sort_content(t_var *envvar);
int			ft_handle_export_args(t_minishell *shell);
int			ft_handle_no_equal(t_minishell *shell, t_arg *argument);
bool		ft_handle_with_equal(t_minishell *shell, t_arg *argument);

// OPTIONS
bool		ft_check_options(t_minishell *shell, t_arg *arg);

//TTY
void		edit_termios(void);

// VARIABLES
void		ft_varadd_back(t_var **lst, t_var *new);
t_var		*ft_create_envvar_list(char **envp);

//SIGNALS
void		handle_sigint(int sig);
void		config_signals(int process_type);
void		redefine_child_signals(void);
void		ignore_some_signals(void);

// FTS_PIPE_REDIR_UTILS
bool		is_pipe_or_redir(t_cmd *cmd, int i);
bool		is_file(t_cmd *cmd);
bool		ft_has_pipe(t_cmd *cmd_temp);
void		ft_nopipe(int in_fd, int out_fd);
void		ft_haspipe(int in_fd, int out_fd, int fd1, int fd0);

void		create_pipe(int fd[2]);

void		ft_execute_cmd(t_cmd *command, char **arguments, char **env_var);
void		ft_get_path(t_cmd *commands);
char		*get_command_path(char *command);
void		define_in_out_fd(t_cmd *cmd_temp, int *in_fd, int *out_fd);
void		create_pipe(int fd[2]);
void		handle_pipe_and_redir(t_minishell *shell, t_cmd *commands);
int			heredoc(t_minishell *shell);
int			process_heredoc_cmds(t_minishell *shell, \
struct sigaction *sa_original);
int			ft_pipe_redir_loop(t_minishell *shell, \
t_cmd *commands, int fd[2], int old_read_fd);
bool		is_file(t_cmd *cmd);
bool		is_pipe_or_redir(t_cmd *cmd, int i);
void		ft_exec(t_minishell *shell, t_cmd *cmd_temp);
#endif