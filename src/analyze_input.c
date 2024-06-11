/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/11 18:56:53 by brunhenr         ###   ########.fr       */
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
	i = 0;
	while (dirs[i] != NULL)
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
		i++;
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

static char **to_array(t_arg **arguments)
{
	int		i;
	char	**array;

	i = 0;
	while (arguments[i]->arg != NULL)
		i++;
	array = (char **)malloc(sizeof(char *) * (i + 1));
	i = -1;
	while (arguments[++i]->arg != NULL)
		array[i] = ft_strdup(arguments[i]->arg);
	array[i] = NULL;
	return (array);
}

static void	handle_command(t_token **commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;
	char	**arguments;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		command_path = get_command_path(commands[0]->cmd);
		arguments = to_array(commands[0]->argument);
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

void	handle_export(t_var *envvar_list, t_minishell *shell)
{
	t_var	*current;

	//printf("arguments: %s\n", (*shell->tokens)->argument[0]->arg);
	//printf("arguments: %s\n", (*shell->tokens)->argument[1]->arg);
	//printf("arguments: %s\n", (*shell->tokens)->argument[2]->arg);
	if ((*shell->tokens)->argument[1]->arg == NULL)
	{
		current = envvar_list;
		while (current != NULL)
		{
			if (current->exp == true)
				printf("declare -x %s\n", current->content);
			current = current->next;
		}
	}
	/*
	else
	{
		while ((*shell->tokens)->argument[1]->arg != NULL)
		{
			current = find_envvar(envvar_list, (*shell->tokens)->argument[1]->arg);
			if (current == NULL)
				{}//add new envvar to envvar_list with bool env = false
			else
				if (ft_strchr((*shell->tokens)->argument[1]->arg, ('=' * -1)) == NULL)
					current->exp = true;
				else

				edit_envvar(current, (*shell->tokens)->argument[1]->arg, (*shell->tokens)->argument[2]->arg);
			(*shell->tokens)->argument[1]++;
		}
	}
	*/
}

void	handle_env(t_var *envvar_list, t_minishell *shell)
{
	t_var	*current;

	//problema de free(): invalid pointer detected meio aleatorio conforme o tamanho do input
	if (shell->tokens[0]->argument[1]->arg != NULL)
	{
		printf("env: %s: No such file or directory\n", shell->tokens[0]->argument[1]->arg);
		return ;
	}
	current = envvar_list;
	while (current != NULL)
	{
		if (current->env == true)
			printf("%s\n", current->content);
		current = current->next;
	}
}

void	handle_unset(t_token **tokens, t_var **envvar_list)
{
	t_var	*envvar;
	int		i;

	if ((*tokens)->argument[1]->arg == NULL)
		return ;
	i = 1;
	while ((*tokens)->argument[i] != NULL)
	{
		envvar = find_envvar(*envvar_list, (*tokens)->argument[i]->arg);
		if (envvar != NULL)
			remove_envvar(envvar_list, envvar);
		i++;
	}
}

void	analyze_input(t_minishell *shell)
{
	parsing_hub(shell->input, shell);
	if (shell->tokens[0]->cmd != NULL)
	{
		if (ft_strcmp(shell->tokens[0]->cmd, "=") == 0)
			handle_equal(shell, shell->tokens[0]);
		else if (ft_strcmp(shell->tokens[0]->cmd, "cd") == 0)
			handle_cd(shell->tokens, shell);
		else if (ft_strcmp(shell->tokens[0]->cmd, "echo") == 0)
			handle_echo(shell->tokens);
		else if (ft_strcmp(shell->tokens[0]->cmd, "exit") == 0)
			handle_exit(shell);
		else if (ft_strcmp(shell->tokens[0]->cmd, "export") == 0)
			handle_export(shell->envvars, shell);
		else if (ft_strcmp(shell->tokens[0]->cmd, "unset") == 0)
			handle_unset(shell->tokens, &shell->envvars);
		else if (ft_strcmp(shell->tokens[0]->cmd, "env") == 0)
			handle_env(shell->envvars, shell);
		else if (shell->tokens[0] != NULL)
			handle_command(shell->tokens);
	}
	return ;
}
