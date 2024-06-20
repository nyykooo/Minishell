/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:09:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/20 17:58:40 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static char **envvar_array(t_minishell *shell)
{
	t_var	*temp;
	char	**env_var;
	int		i;

	i = 0;
	temp = shell->envvars;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	env_var = (char **)malloc(sizeof(char *) * (i + 1));
	if (!env_var)
	{
		//free everything
		printf("Error: failed to allocate memory %s\n", strerror(errno));
		exit (1);
	}
	temp = shell->envvars;
	i = -1;
	while (temp)
	{
		env_var[i] = ft_strdup(temp->content);
		temp = temp->next;
	}
	env_var[i] = NULL;
	return (env_var);
}

void	handle_exec(t_minishell *shell, t_cmd *commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;
	char	**arguments;
	char 	**env_var;

	(void)shell;
	status = 0;
	pid = fork();
	command_path = ft_strdup(commands->cmd + 2);
	commands->cmd = ft_strdup(commands->cmd + 2);
	env_var = envvar_array(shell);
	if (pid == 0)
	{
		arguments = ft_to_array(commands);
		if (command_path == NULL || execve(command_path, arguments, env_var) == -1)
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
