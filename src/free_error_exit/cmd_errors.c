/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:01 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/06 16:50:45 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	ft_execute_cmd(t_cmd *command, char **arguments, char **env_var)
{
	if (execve(command->path, arguments, env_var) == -1)
	{
		ft_print_error(false, 127, 3,
			"-minishell: ", command->cmd, ": command not found\n");
		free(command->path);
		free(arguments);
		free_array(env_var);
		free_shell(command->shell);
		exit(command->shell->exit_status);
	}
}

static void	ft_verify_path(t_cmd *command)
{
	if (command->path == NULL)
		ft_print_error(true, 127, 3,
			"-minishell: ", command->cmd, ": command not found\n");
}

static void	ft_analyze_cmd_stat(t_cmd *command)
{
	struct stat	buf;

	if (stat(command->cmd, &buf) == 0)
	{
		if (buf.st_mode & __S_IFDIR && (ft_strncmp(command->cmd, "./", 2) == 0
				|| command->cmd[0] == '/'))
			ft_print_error(true, 126, 3,
				"-minishell: ", command->cmd, ": Is a directory\n");
		else if (access(command->cmd, X_OK) != 0
			&& ft_strncmp(command->cmd, "./", 2) == 0)
			ft_print_error(true, 126, 3,
				"-minishell: ", command->cmd, ": Permission denied\n");
	}
	else
	{
		if (ft_strncmp(command->cmd, "./", 2) == 0 || command->cmd[0] == '/')
			ft_print_error(true, 127, 3,
				"-minishell: ", command->cmd, ": No such file or directory\n");
		ft_verify_path(command);
	}
}

void	ft_analyze_cmd(t_cmd *command)
{
	char	**arguments;
	char	**env_var;

	ft_analyze_cmd_stat(command);
	arguments = ft_to_array(command);
	env_var = envvar_array(command->shell);
	ft_execute_cmd(command, arguments, env_var);
}
