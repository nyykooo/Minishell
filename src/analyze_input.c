/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/07 12:56:36 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"
#include <string.h>
#include <stdlib.h>

void	ft_get_path(t_cmd *commands)
{
	if (access(commands->cmd, X_OK) != 0)
		commands->path = get_command_path(commands->cmd);
	else
		commands->path = ft_strdup(commands->cmd);
}

static void	handle_command(t_cmd *commands, t_minishell *shell)
{
	pid_t	pid;

	ignore_some_signals();
	pid = fork();
	if (pid == 0)
	{
		redefine_child_signals();
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
	}
	config_signals(0);
}

static void	handle_cmds(t_minishell *shell)
{
	ft_get_path(shell->commands);
	ft_update_underlinevar(shell);
	if (ft_strcmp(shell->commands->cmd, "cd") == 0)
		handle_cd(shell->commands, shell);
	else if (ft_strcmp(shell->commands->cmd, "echo") == 0)
		handle_echo(shell->commands);
	else if (ft_strcmp(shell->commands->cmd, "exit") == 0)
		handle_exit(shell->commands, shell);
	else if (ft_strcmp(shell->commands->cmd, "export") == 0)
		shell->exit_status = handle_export(shell);
	else if (ft_strcmp(shell->commands->cmd, "unset") == 0)
		handle_unset(shell->commands, &shell->envvars);
	else if (ft_strcmp(shell->commands->cmd, "env") == 0)
		handle_env(shell->envvars, shell, shell->commands);
	else if (ft_strcmp(shell->commands->cmd, "pwd") == 0)
		handle_pwd(shell);
	else if (shell->commands != NULL)
		handle_command(shell->commands, shell);
	free(shell->commands->path);
}

void	ft_analyze_input(t_minishell *shell)
{
	int	status;

	status = 0;
	parsing_hub(shell);
	if (shell->n_cmd == 0)
		return ;
	status = heredoc(shell);
	if (WIFEXITED(status) == true && WEXITSTATUS(status) == 130)
	{
		shell->exit_status = 130;
		return ;
	}
	if (shell->n_cmd > 1 || (ft_strcmp(shell->commands->cmd, ">") == 0))
		handle_pipe_and_redir(shell, shell->commands);
	else if (shell->commands)
	{
		if (shell->commands->type == T_EQUAL)
			ft_handle_equal(shell, shell->commands);
		if (shell->commands->type == T_COMMAND)
			handle_cmds(shell);
	}
	return ;
}
