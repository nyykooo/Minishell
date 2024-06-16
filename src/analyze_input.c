/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/16 16:57:04 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"
#include <string.h>
#include <stdlib.h>

static char	*get_command_path(char *command)
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
		possible_path = malloc (strlen(dirs[i]) + strlen(command) + 2);
		strcpy (possible_path, dirs[i]);
		strcat (possible_path, "/");
		strcat (possible_path, command);
		if (access(possible_path, X_OK) == 0)
		{
			free(dirs);
			return (possible_path);
		}
		free (possible_path);
	}
	i = 0;
	while (dirs[i] != NULL)
		free(dirs[i++]);
	free(dirs);
	return (NULL);
}

void	handle_exit(t_minishell *shell)
{
	free_shell(shell);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

static char	**to_array(t_cmd *command)
{
	int		i;
	char	**array;
	t_arg	*tmp;

	i = 0;
	tmp = command->arguments;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	array = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (command->arguments != NULL)
	{
		array[i++] = ft_strdup(command->arguments->arg);
		command->arguments = command->arguments->next;
	}
	array[i] = NULL;
	return (array);
}

static void	handle_command(t_cmd *commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;
	char	**arguments;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		command_path = get_command_path(commands->cmd);
		arguments = to_array(commands);
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

void	analyze_input(t_minishell *shell)
{
	parsing_hub(shell);
	if (shell->commands)
	{
		if (ft_strcmp(shell->commands->cmd, "=") == 0)
			handle_equal(shell, shell->commands);
		else if (ft_strcmp(shell->commands->cmd, "cd") == 0)
			handle_cd(shell->commands, shell);
		else if (ft_strcmp(shell->commands->cmd, "echo") == 0)
			handle_echo(shell->commands);
		else if (ft_strcmp(shell->commands->cmd, "exit") == 0)
			handle_exit(shell);
		else if (ft_strcmp(shell->commands->cmd, "export") == 0)
			handle_export(shell->envvars, shell);
		else if (ft_strcmp(shell->commands->cmd, "unset") == 0)
			handle_unset(shell->commands, &shell->envvars);
		else if (ft_strcmp(shell->commands->cmd, "env") == 0)
			handle_env(shell->envvars, shell);
		else if (shell->commands != NULL)
			handle_command(shell->commands);
	}
	return ;
}

// void	analyze_input(t_minishell *shell)
// {
// 	parsing_hub(shell);
// 	if (shell->tokens[0]->cmd != NULL)
// 	{
// 		if (ft_strcmp(shell->tokens[0]->cmd, "=") == 0)
// 			handle_equal(shell, shell->tokens[0]);
// 		else if (ft_strcmp(shell->tokens[0]->cmd, "cd") == 0)
// 			handle_cd(shell->tokens, shell);
// 		else if (ft_strcmp(shell->tokens[0]->cmd, "echo") == 0)
// 			handle_echo(shell->tokens);
// 		else if (ft_strcmp(shell->tokens[0]->cmd, "exit") == 0)
// 			handle_exit(shell);
// 		else if (ft_strcmp(shell->tokens[0]->cmd, "export") == 0)
// 			handle_export(shell->envvars, shell);
// 		else if (ft_strcmp(shell->tokens[0]->cmd, "unset") == 0)
// 			handle_unset(shell->tokens, &shell->envvars);
// 		else if (ft_strcmp(shell->tokens[0]->cmd, "env") == 0)
// 			handle_env(shell->envvars, shell);
// 		else if (shell->tokens[0] != NULL)
// 			handle_command(shell->tokens);
// 	}
// 	return ;
// }
