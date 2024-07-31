/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 16:12:01 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/31 17:54:17 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static void	ft_execute_cmd(t_cmd *command, char **arguments, char **env_var)
{
	if (execve(command->path, arguments, env_var) == -1)
		{
			command->shell->error_msg = error_msg_construct(3, "-minishell: ", command->cmd, ": command not found\n");
			command->shell->exit_status = put_error_msg(command->shell->error_msg, 127);
			free(command->path);
			free(arguments);
			free_array(env_var);
			free_shell(command->shell);
			exit(command->shell->exit_status);	
		}
}

static bool	ft_verify_path(t_cmd *command)
{
	if (command->path == NULL)
	{
		command->shell->error_msg = error_msg_construct(3, "-minishell: ", command->cmd, ": command not found\n");
		command->shell->exit_status = put_error_msg(command->shell->error_msg, 127);
		return (true);
	}
	return (false);
}

static bool	ft_analyze_cmd_stat(t_cmd *command)
{
	struct stat	buf;
	if (stat(command->cmd, &buf) == 0)
	{
		if (buf.st_mode & __S_IFDIR && (ft_strncmp(command->cmd, "./", 2) == 0 || command->cmd[0] == '/'))
		{
			command->shell->error_msg = error_msg_construct(3, "-minishell: ", command->cmd, ": Is a directory\n");
			command->shell->exit_status = put_error_msg(command->shell->error_msg, 126);
			return (true);
		}
		else if (access(command->cmd, X_OK) != 0 && ft_strncmp(command->cmd, "./", 2) == 0)
		{
			command->shell->error_msg = error_msg_construct(3, "-minishell: ", command->cmd, ": Permission denied\n");
			command->shell->exit_status = put_error_msg(command->shell->error_msg, 126);
			return (true);
		}
	}
	else
	{
		if (ft_strncmp(command->cmd, "./", 2) == 0 || command->cmd[0] == '/')
		{
			command->shell->error_msg = error_msg_construct(3, "-minishell: ", command->cmd, ": No such file or directory\n");
			command->shell->exit_status = put_error_msg(command->shell->error_msg, 127);
			return (true);			
		}
		if (ft_verify_path(command) == true)
			return (true);
	}
	return (false);
}


void	ft_analyze_cmd(t_cmd *command)
{
	char	**arguments;
	char	**env_var;

	if (ft_analyze_cmd_stat(command) == true)
	{
		free_shell(command->shell);
		exit(command->shell->exit_status);		
	}	
	arguments = ft_to_array(command);
	env_var = envvar_array(command->shell);
	ft_execute_cmd(command, arguments, env_var);
	
}
