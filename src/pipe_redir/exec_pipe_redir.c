/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_redir.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 17:08:41 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/06 21:46:55 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	free_dirs(char **dirs)
{
	int	i;

	i = 0;
	if (dirs == NULL)
		return ;
	while (dirs[i] != NULL)
		free(dirs[i++]);
	free(dirs);
}

char	*get_command_path(char *command)
{
	char	*path;
	char	**dirs;
	char	*possible_path;
	int		i;

	path = getenv ("PATH");
	dirs = ft_split (path, ':');
	i = -1;
	while (dirs[++i] != NULL)
	{
		possible_path = malloc (ft_strlen(dirs[i]) + ft_strlen(command) + 2);
		ft_strcpy (possible_path, dirs[i]);
		ft_strcat (possible_path, "/");
		ft_strcat (possible_path, command);
		if (access(possible_path, X_OK) == 0)
		{
			free_dirs(dirs);
			return (possible_path);
		}
		free (possible_path);
	}
	free_dirs(dirs);
	return (NULL);
}

bool	is_builtin(char *cmd)
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
		handle_cd(cmd_temp, shell);
	else if (ft_strcmp(cmd_temp->cmd, "echo") == 0)
		handle_echo(cmd_temp);
	else if (ft_strcmp(cmd_temp->cmd, "exit") == 0)
		handle_exit(cmd_temp, shell);
	else if (ft_strcmp(cmd_temp->cmd, "export") == 0)
		handle_export(shell);
	else if (ft_strcmp(cmd_temp->cmd, "unset") == 0)
		handle_unset(cmd_temp, &shell->envvars);
	else if (ft_strcmp(cmd_temp->cmd, "env") == 0)
		handle_env(shell->envvars, shell, cmd_temp);
	else if (ft_strcmp(cmd_temp->cmd, "pwd") == 0)
		handle_pwd(shell);
}

void	ft_exec(t_minishell *shell, t_cmd *cmd_temp)
{
	char	**arg_array;

	if (is_builtin(cmd_temp->cmd) == true)
	{
		ft_exec_builtin(shell, cmd_temp);
		exit(shell->exit_status);
	}
	arg_array = ft_to_array(cmd_temp);
	ft_get_path(cmd_temp);
	ft_execute_cmd(cmd_temp, arg_array, envvar_array(shell));
}
