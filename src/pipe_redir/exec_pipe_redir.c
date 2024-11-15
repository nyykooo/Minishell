/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:08:41 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/16 18:11:40 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_free_dirs(char **dirs)
{
	int	i;

	i = 0;
	if (dirs == NULL)
		return ;
	while (dirs[i] != NULL)
		free(dirs[i++]);
	free(dirs);
}

char	*ft_get_command_path(char *command, t_minishell *shell)
{
	t_var		*path;
	char		**dirs;
	char		*possible_path;
	int			i;

	path = ft_find_envvar(shell->envvars, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split (path->value, ':');
	i = -1;
	while (dirs[++i] != NULL)
	{
		possible_path = malloc (ft_strlen(dirs[i]) + ft_strlen(command) + 2);
		ft_strcpy (possible_path, dirs[i]);
		ft_strcat (possible_path, "/");
		ft_strcat (possible_path, command);
		if (access(possible_path, X_OK) == 0)
		{
			ft_free_dirs(dirs);
			return (possible_path);
		}
		free (possible_path);
	}
	ft_free_dirs(dirs);
	return (ft_strdup(command));
}

bool	ft_is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0 || \
	ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 || \
	ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0 || \
	ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

void	ft_exec_builtin(t_minishell *shell, t_cmd *cmd_temp)
{
	if (ft_strcmp(cmd_temp->cmd, "cd") == 0)
		ft_handle_cd(cmd_temp, shell);
	else if (ft_strcmp(cmd_temp->cmd, "echo") == 0)
		ft_handle_echo(cmd_temp);
	else if (ft_strcmp(cmd_temp->cmd, "exit") == 0)
		ft_handle_exit(cmd_temp, shell);
	else if (ft_strcmp(cmd_temp->cmd, "export") == 0)
		shell->exit_status = ft_handle_export(shell);
	else if (ft_strcmp(cmd_temp->cmd, "unset") == 0)
		ft_handle_unset(cmd_temp, &shell->envvars);
	else if (ft_strcmp(cmd_temp->cmd, "env") == 0)
		ft_handle_env(shell->envvars, cmd_temp);
	else if (ft_strcmp(cmd_temp->cmd, "pwd") == 0)
		ft_handle_pwd(shell);
}

void	ft_exec(t_minishell *shell, t_cmd *cmd_temp)
{
	ft_close_survivors_fds();
	if (ft_is_builtin(cmd_temp->cmd) == true)
	{
		ft_exec_builtin(shell, cmd_temp);
		ft_free_shell(shell);
		exit(shell->exit_status);
	}
	if ((!cmd_temp->prev || cmd_temp->prev->type == T_PIPE) && \
	(strcmp(cmd_temp->cmd, ">") == 0 || \
	strcmp(cmd_temp->cmd, ">>") == 0))
	{
		ft_free_shell(shell);
		exit(0);
	}
	ft_get_path(cmd_temp);
	ft_analyze_cmd(cmd_temp);
}
