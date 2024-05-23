/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/05/23 22:31:56 by ncampbel         ###   ########.fr       */
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

static void	handle_cd(char **commands)
{
	char	*dir; 

	dir = commands[1];
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
}

static void	handle_exit(char **commands)
{
	int	i;

	i = 0;
	while (commands[i] != NULL)
		free(commands[i++]);
	free(commands);
}

static void	handle_command(char **commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		command_path = get_command_path(commands[0]);
		if (command_path == NULL)
		{
			perror ("minishell");
			exit (EXIT_FAILURE);
		}
		if (execve(command_path, commands, NULL) == -1)
		{
			perror("minishell");
			free(command_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
		perror ("minishell");
	else
		waitpid (pid, &status, WUNTRACED);
}

void	print_export(t_envvar *envvar_list)
{
	t_envvar	*current;

	current = envvar_list;
	while (current != NULL)
	{
		printf("declare -x %s\n", current->content);
		current = current->next;
	}
}

void	print_env(t_envvar *envvar_list)
{
	t_envvar	*current;

	current = envvar_list;
	while (current != NULL)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

t_envvar	*find_envvar(t_envvar *envvar_list, char *name)
{
	t_envvar	*current;
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

void	remove_envvar(t_envvar **envvar_list, t_envvar *envvar)
{
	t_envvar	*current;
	t_envvar	*prev;

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

void	handle_unset(char **commands, t_envvar **envvar_list)
{
	t_envvar	*envvar;

	if (commands[1] == NULL)
		return ;
	envvar = find_envvar(*envvar_list, commands[1]);
	if (envvar != NULL)
		remove_envvar(envvar_list, envvar);
}

void	analyze_input(char *input, t_envvar **envvar_list)
{
	char	**commands;
	char *temp;
	int		i;

	i = 0;
	if (!input)
		return ;
	temp = ft_strdup(input);
	// commands = mega_parsing(input);
	commands = parsing_hub(temp);
	if (ft_strcmp(commands[0], "cd") == 0)
		handle_cd(commands);
	else if (ft_strcmp(commands[0], "exit") == 0)
	{
		handle_exit(commands);
		return ;
	}
	else if (ft_strcmp(commands[0], "export") == 0)
		print_export(*envvar_list);
	else if (ft_strcmp(commands[0], "unset") == 0)
		handle_unset(commands, envvar_list);
	else if (ft_strcmp(commands[0], "env") == 0)
		print_env(*envvar_list);
	else if (commands[0] != NULL)
		handle_command(commands);
	if (commands != NULL)
	{
		while (commands[i] != NULL)
			free(commands[i++]);
		free(commands);
	}
	free(temp);
	return ;
}
