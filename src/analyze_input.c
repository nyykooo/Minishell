/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/06 17:13:59 by brunhenr         ###   ########.fr       */
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

	if (access(command, X_OK) == 0)
		return (command);
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

static void	get_path(t_cmd *commands)
{
	if (access(commands->cmd, X_OK) == 0)
		commands->path = ft_strdup(commands->cmd);
	else
		commands->path = get_command_path(commands->cmd);
}

static void	handle_command(t_cmd *commands, t_minishell *shell)
{
	pid_t	pid;
	char	**arguments;
	char	**env_var;

	pid = fork();
	if (pid == 0)
	{
		get_path(commands);
		arguments = ft_to_array(commands);
		env_var = envvar_array(shell);
		if (commands->path == NULL || execve(commands->path, arguments, env_var) == -1)
		{
			printf("%s: command not found\n", commands->cmd);
			//perror("minishell");
			if (commands->path != NULL)
				free(commands->path);
			exit(EXIT_FAILURE);
		}
		free(commands->path);
		free(arguments);
	}
	else if (pid < 0)
		perror ("minishell");
	else
		waitpid (pid, &(shell->exit_status), WUNTRACED);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
}

static void	handle_builtins(t_minishell *shell)
{
		if (ft_strcmp(shell->commands->cmd, "cd") == 0)
			handle_cd(shell->commands, shell);
		else if (ft_strcmp(shell->commands->cmd, "echo") == 0)
			handle_echo(shell->commands);
		else if (ft_strcmp(shell->commands->cmd, "exit") == 0)
			handle_exit(shell->commands, shell);
		else if (ft_strcmp(shell->commands->cmd, "export") == 0)
			handle_export(shell);
		else if (ft_strcmp(shell->commands->cmd, "unset") == 0)
			handle_unset(shell->commands, &shell->envvars);
		else if (ft_strcmp(shell->commands->cmd, "env") == 0)
			handle_env(shell->envvars, shell);
		else if (ft_strcmp(shell->commands->cmd, "pwd") == 0)
			handle_pwd(shell);
		else if (shell->commands != NULL)
			handle_command(shell->commands, shell);
}

void	analyze_input(t_minishell *shell)
{
	//t_cmd *temp;
	
	parsing_hub(shell);
	/*temp = shell->commands;
	while (temp)
	{
		printf("temp->cmd: %s\n", temp->cmd);
		printf("temp->type: %d\n", temp->type);
		printf("temp->rtrunc: %d\n", temp->rtrunc);
		printf("temp->rappend: %d\n", temp->rappend);
		printf("temp->lappend: %d\n", temp->lappend);
		printf("temp->input_file: %d\n", temp->input_file);
		printf("temp->path: %s\n", temp->path);
		printf("----------------\n");
		temp = temp->next;
	}*/
	if (shell->n_cmd > 1 || (ft_strcmp(shell->commands->cmd, ">") == 0)) //Isso implica que temos |, &&, ||, ;, (), {}. Ou merameante <, >, >>, <<.
		handle_pipe_and_redir(shell->commands);
	else if (shell->commands)
	{
		if (shell->commands->type == T_EQUAL)
			handle_equal(shell, shell->commands);
		if (shell->commands->type == T_COMMAND)
			handle_builtins(shell);
	}
	return ;
}
