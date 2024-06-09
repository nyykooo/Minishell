/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/08 19:45:04 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"
#include <string.h>
#include <stdlib.h>

// static char	*get_command_path(char *command)
// {
// 	char	*path;
// 	char	**dirs;
// 	char	*possible_path;
// 	int		i;

// 	path = getenv ("PATH");
// 	dirs = ft_split (path, ':');
// 	i = 0;
// 	while (dirs[i] != NULL)
// 	{
// 		possible_path = malloc (strlen(dirs[i]) + strlen(command) + 2);
// 		strcpy (possible_path, dirs[i]);
// 		strcat (possible_path, "/");
// 		strcat (possible_path, command);
// 		if (access(possible_path, X_OK) == 0)
// 		{
// 			free(dirs);
// 			return (possible_path);
// 		}
// 		free (possible_path);
// 		i++;
// 	}
// 	i = 0;
// 	while (dirs[i] != NULL)
// 		free(dirs[i++]);
// 	free(dirs);
// 	return (NULL);
// }

static void	handle_cd(t_token **commands)
{
	char	*dir; 
	
	dir = ft_strdup(commands[0]->argument[1]->arg);
	if (dir == NULL)
	{
		dir = getenv("HOME");
		if (dir == NULL)
		{
			write(2, "cd: HOME not set\n", 17);
			return ;
		}
	}
	if (chdir(dir) == -1)
		write(2, "cd: no such file or directory\n", 30);
	free(dir);
}

static void	handle_exit(t_minishell *shell)
{
	free_shell(shell);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

// static void	handle_command(t_token **commands)
// {
// 	pid_t	pid;
// 	char	*command_path;
// 	int		status;

// 	status = 0;
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		command_path = get_command_path(commands[0]->cmd);
// 		if (command_path == NULL)
// 		{
// 			perror ("minishell");
// 			exit (EXIT_FAILURE);
// 		}
// 		if (execve(command_path, commands[0]->argument, NULL) == -1)
// 		{
// 			perror("minishell");
// 			free(command_path);
// 			exit(EXIT_FAILURE);
// 		}
// 	}
// 	else if (pid < 0)
// 		perror ("minishell");
// 	else
// 		waitpid (pid, &status, WUNTRACED);
// }

void	print_export(t_var *envvar_list)
{
	t_var	*current;

	current = envvar_list;
	while (current != NULL)
	{
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
}

void	print_env(t_var *envvar_list)
{
	t_var	*current;

	current = envvar_list;
	while (current != NULL)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

t_var	*find_envvar(t_var *envvar_list, char *name)
{
	t_var	*current;
	size_t		name_len;

	name_len = strlen(name);
	current = envvar_list;
	while (current != NULL)
	{
		if (strncmp(current->content, name, name_len) == 0 \
		&& current->content[name_len] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	remove_envvar(t_var **envvar_list, t_var *envvar)
{
	t_var	*current;
	t_var	*prev;

	current = *envvar_list;
	prev = NULL;
	while (current != NULL)
	{
		if (current == envvar)
		{
			if (prev == NULL)
				*envvar_list = current->next;
			else
				prev->next = current->next;
			free(current->content);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

void	handle_unset(t_token **commands, t_var **envvar_list)
{
	t_var	*envvar;

	if (commands[0] == NULL)
		return ;
	envvar = find_envvar(*envvar_list, commands[0]->argument[0]->arg);
	if (envvar != NULL)
		remove_envvar(envvar_list, envvar);
}

void	analyze_input(t_minishell *shell)
{
	shell->tokens = parsing_hub(shell->input);
	if (shell->tokens[0] == NULL)
		return ;
	if (shell->tokens[0]->cmd != NULL)
	{
		if (ft_strcmp(shell->tokens[0]->cmd, "=") == 0)
			handle_equal(shell, shell->tokens[0]);
		else if (ft_strcmp(shell->tokens[0]->cmd, "cd") == 0)
			handle_cd(shell->tokens);
		else if (ft_strcmp(shell->tokens[0]->cmd, "echo") == 0)
			handle_echo(shell->tokens);
		else if (ft_strcmp(shell->tokens[0]->cmd, "exit") == 0)
			handle_exit(shell);
		else if (ft_strcmp(shell->tokens[0]->cmd, "export") == 0)
			print_export(shell->envvars);
		else if (ft_strcmp(shell->tokens[0]->cmd, "unset") == 0)
			handle_unset(shell->tokens, &shell->envvars);
		else if (ft_strcmp(shell->tokens[0]->cmd, "env") == 0)
			print_env(shell->envvars);
		else if (shell->tokens[0] != NULL)
			return ;
				// handle_command(shell->tokens);
	}
}
