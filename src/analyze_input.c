/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/13 22:47:33 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"
#include <string.h>
#include <stdlib.h>

void	ft_get_path(t_cmd *commands)
{
	if (access(commands->cmd, X_OK) != 0)
		commands->path = ft_get_command_path(commands->cmd, commands->shell);
	else
		commands->path = ft_strdup(commands->cmd);
}

void	define_exit_status(t_minishell *shell)
{
	if (WTERMSIG(shell->exit_status) == SIGQUIT)
	{
		shell->exit_status = 131;
		printf("Quit\n");
	}
	else if (WTERMSIG(shell->exit_status) == SIGINT)
	{
		shell->exit_status = 130;
		printf("\n");
	}
}

static void	handle_command(t_cmd *commands, t_minishell *shell)
{
	pid_t	pid;

	ft_ignore_some_signals();
	pid = fork();
	if (pid == 0)
	{
		ft_redefine_child_signals();
		ft_analyze_cmd(commands);
	}
	else if (pid < 0)
		perror ("minishell");
	else
	{
		waitpid (pid, &(shell->exit_status), WUNTRACED);
		if (WIFEXITED(shell->exit_status))
			shell->exit_status = WEXITSTATUS(shell->exit_status);
		else if (WIFSIGNALED(shell->exit_status) \
		|| WIFSTOPPED(shell->exit_status))
		{
			define_exit_status(shell);
		}
	}
	ft_config_signals(0);
}

static void	handle_cmds(t_minishell *shell)
{
	ft_get_path(shell->commands);
	ft_update_underlinevar(shell);
	if (ft_strcmp(shell->commands->cmd, "cd") == 0)
		ft_handle_cd(shell->commands, shell);
	else if (ft_strcmp(shell->commands->cmd, "echo") == 0)
		ft_handle_echo(shell->commands);
	else if (ft_strcmp(shell->commands->cmd, "exit") == 0)
		ft_handle_exit(shell->commands, shell);
	else if (ft_strcmp(shell->commands->cmd, "export") == 0)
		shell->exit_status = ft_handle_export(shell);
	else if (ft_strcmp(shell->commands->cmd, "unset") == 0)
		ft_handle_unset(shell->commands, &shell->envvars);
	else if (ft_strcmp(shell->commands->cmd, "env") == 0)
		ft_handle_env(shell->envvars, shell->commands);
	else if (ft_strcmp(shell->commands->cmd, "pwd") == 0)
		ft_handle_pwd(shell);
	else if (shell->commands != NULL)
		handle_command(shell->commands, shell);
	free(shell->commands->path);
}

void	ft_analyze_input(t_minishell *shell)
{
	int	status;
	//t_cmd	*cmd_temp;
	//t_token	*tokens;

	status = 0;
	ft_parsing_hub(shell);
	// tokens = shell->tokens;
	// while (tokens != NULL)
	// {
	// 	printf("tokens->content: %s\n", tokens->content);
	// 	tokens = tokens->next;
	// }
	// printf("-----------------------\n");
	if (shell->n_cmd == 0)
		return ;
	status = heredoc(shell);
	if (WIFEXITED(status) == true && WEXITSTATUS(status) == 130)
	{
		shell->exit_status = 130;
		return ;
	}
	// cmd_temp = shell->commands;
	// while (cmd_temp != NULL)
	// {
	// 	printf("cmd_temp->cmd: %s\n", cmd_temp->cmd);
	// 	printf("cmd_temp->type: %d\n", cmd_temp->type);
	// 	printf("cmd_temp->rtunc: %d\n", cmd_temp->rtrunc);
	// 	if (cmd_temp->prev == NULL)
	// 		printf("cmd_temp->prev: ehhhhhhhh NULL\n");
	// 	while (cmd_temp->arguments != NULL)
	// 	{
	// 		printf("arg_temp->arg: %s\n", cmd_temp->arguments->arg);
	// 		cmd_temp->arguments = cmd_temp->arguments->next;
	// 	}
	// 	printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
	// 	cmd_temp = cmd_temp->next;
	// }
	if (shell->n_cmd > 1 || (ft_strcmp(shell->commands->cmd, ">") == 0) || \
	(ft_strcmp(shell->commands->cmd, "<") == 0) \
	|| (ft_strcmp(shell->commands->cmd, ">>") == 0))
		ft_handle_pipe_and_redir(shell, shell->commands);
	else if (shell->commands)
	{
		if (shell->commands->type == T_EQUAL)
			ft_handle_equal(shell, shell->commands);
		if (shell->commands->type == T_COMMAND)
			handle_cmds(shell);
	}
	return ;
}
