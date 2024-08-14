/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 14:21:28 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/14 09:40:58 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "structures.h"

# define HRDC_EOF "-minishell: Warning: \
here-document delimited by end-of-file\n"

t_minishell	*ft_get_shell(void);

void		ft_analyze_input(t_minishell *shell);

// NEW PARSING

void		ft_parsing_hub(t_minishell *shell);

// NEW PARSING - INPUT

int			ft_input_manager(t_minishell *shell);
void		ft_expand_pipes_redir(t_minishell *shell);

// NEW PARSING - TOKENS

void		ft_tokenizer(t_minishell *shell);
void		ft_token_creation(char **array, t_minishell *shell);
// void	ft_analyze_tokens(t_arg **tokens, t_minishell *shell);
void		ft_analyze_tokens(t_token *tokens, t_minishell *shell);
void		ft_include_token(t_minishell *shell, \
char *argument, t_token *token);

// NEW PARSING - COMMANDS

void		ft_create_command(t_token *tokens, t_minishell *shell);
void		ft_include_arg(t_minishell *shell, char *input, t_arg *argument);

// NEW PARSING - ARGUMENTS

void		ft_analyze_arguments(t_minishell *shell, t_cmd *cmd);

// NEW PARSING - QUOTES

void		ft_expand_quotes(t_token *argument, t_minishell *shell);
char		*ft_quote_del(char *input);
int			ft_skip_quotes(char *input, int *i);
int			ft_is_inside_quotes(char *str, size_t index);

// NEW PARSING - EQUAL

bool		ft_check_equal(t_token *token);

// NEW PARSING - DOLLAR

void		ft_expand_dolar(char **input, t_minishell *shell);
void		ft_expand_tildes(char **input, t_minishell *shell);
void		ft_expand_hashtag(char **input);

// FREE_ERROR_EXIT
void		ft_free_shell(t_minishell *shell);
void		ft_free_tokens(t_token *tokens);
void		ft_free_array(char **array);
void		ft_free_list(t_var *head);
void		ft_free_var(t_var *head);
void		ft_free_commands(t_cmd *commands);
char		*ft_error_msg_construct(int nbr, ...);
int			ft_put_error_msg(char *error_msg, int exit_status);
void		ft_analyze_cmd(t_cmd *command);
void		ft_print_error(bool must_free, int exit_status, int nbr, ...);

//ENVVAR_FTS
char		*ft_create_envvar_content(char *name, char *value);
char		*ft_get_value(t_var *envvar_list, char *name);
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
void		ft_handle_cd(t_cmd *command, t_minishell *shell);
void		ft_handle_echo(t_cmd *command);
void		ft_handle_equal(t_minishell *shell, t_cmd *command);
int			ft_handle_export(t_minishell *shell);
void		ft_handle_env(t_var *envvar_list, t_cmd *command);
void		ft_handle_unset(t_cmd *command, t_var **envvar_list);
void		ft_handle_exec(t_minishell *shell, t_cmd *cmd);
void		ft_handle_pwd(t_minishell *shell);
void		ft_handle_exit(t_cmd *command, t_minishell *shell);

// EXPORT
void		ft_print_export(t_var *current);
void		ft_sort_content(t_var *envvar);
int			ft_ft_handle_export_args(t_minishell *shell);
int			ft_handle_no_equal(t_minishell *shell, t_arg *argument);
bool		ft_handle_with_equal(t_minishell *shell, t_arg *argument);

// OPTIONS
bool		ft_check_options(t_arg *arg);

// VARIABLES
void		ft_varadd_back(t_var **lst, t_var *new);
t_var		*ft_create_envvar_list(char **envp);

//SIGNALS
void		ft_handle_sigint(int sig);
void		ft_config_signals(int process_type);
void		ft_redefine_child_signals(void);
void		ft_ignore_some_signals(void);

// FTS_PIPE_REDIR_UTILS
bool		ft_is_pipe_or_redir(t_cmd **cmd, int i);
bool		ft_is_file(t_cmd *cmd);
bool		ft_has_pipe(t_cmd *cmd_temp);
void		ft_nopipe(int in_fd, int out_fd);
void		ft_haspipe(int in_fd, int out_fd, int fd1, int fd0);

void		ft_create_pipe(int fd[2]);

void		ft_execute_cmd(t_cmd *command, char **arguments, char **env_var);
void		ft_get_path(t_cmd *commands);
char		*ft_get_command_path(char *command, t_minishell *shell);
void		ft_define_in_out_fd(t_cmd *cmd_temp, int *in_fd, int *out_fd);
void		ft_create_pipe(int fd[2]);
void		ft_handle_pipe_and_redir(t_minishell *shell, t_cmd *commands);
int			heredoc(t_minishell *shell);
int			process_heredoc_cmds(t_minishell *shell, \
struct sigaction *sa_original);
int			ft_pipe_redir_loop(t_minishell *shell, \
t_cmd *commands, int fd[2], int old_read_fd);
void		ft_exec(t_minishell *shell, t_cmd *cmd_temp);
bool		ft_verify_unexpected_token(t_minishell *shell);
bool		ft_verify_fn(t_minishell *shell);
void		ft_mark_commands(t_minishell *shell);
bool		is_not_pipe_or_redir_arg(t_cmd **cmd);

#endif