/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:09:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/19 17:32:22 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	handle_exec(t_minishell *shell, t_cmd *commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;
	char	**arguments;

	(void)shell;
	status = 0;
	pid = fork();
	command_path = ft_strdup(commands->cmd + 2);
	commands->cmd = ft_strdup(commands->cmd + 2);
	if (pid == 0)
	{
		arguments = ft_to_array(commands);
		if (command_path == NULL || execve(command_path, arguments, NULL) == -1)
		{
			perror("minishell");
			if (command_path != NULL)
				free(command_path);
			exit(EXIT_FAILURE);
		}
		free(command_path);
		free(arguments);
	}
	else if (pid < 0)
		perror ("minishell");
	else
		waitpid (pid, &status, WUNTRACED);
}
