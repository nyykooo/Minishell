/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/05 16:51:00 by brunhenr         ###   ########.fr       */
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

static void	handle_exit(t_minishell *shell)
{
	free_shell(shell);
	printf("exit\n");
	exit(EXIT_SUCCESS);
}

static void	handle_command(t_token **commands)
{
	pid_t	pid;
	char	*command_path;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		command_path = get_command_path(commands[0]->cmd);
		if (command_path == NULL)
		{
			perror ("minishell");
			exit (EXIT_FAILURE);
		}
		if (execve(command_path, commands[0]->argument, NULL) == -1)
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

void	handle_unset(t_token **commands, t_var **envvar_list)
{
	t_var	*envvar;

	if (commands[0] == NULL)
		return ;
	envvar = find_envvar(*envvar_list, commands[0]->argument[0]);
	if (envvar != NULL)
		remove_envvar(envvar_list, envvar);
}

void	analyze_input(char *input, t_minishell *shell)
{
	if (!input)
		return ;
	shell->input = ft_strdup(input);
	shell->tokens = parsing_hub(shell->input);
	/*while (1)
	{
		printf("shell->tokens->cmd: %s\n", shell->tokens[0]->cmd);
		printf("shell->tokens->argument[0]: %s\n", shell->tokens[0]->argument[0]);
		printf("shell->tokens->argument[1]: %s\n", shell->tokens[0]->argument[1]);
		printf("shell->tokens->argument[2]: %s\n", shell->tokens[0]->argument[2]);

		return ;
	}*/
	if (ft_strcmp(shell->tokens[0]->cmd, "cd") == 0)
		handle_cd(shell->tokens, shell);
	else if (ft_strcmp(shell->tokens[0]->cmd, "exit") == 0)
		handle_exit(shell);
	else if (ft_strcmp(shell->tokens[0]->cmd, "export") == 0)
		print_export(shell->envvars);
	else if (ft_strcmp(shell->tokens[0]->cmd, "unset") == 0)
		handle_unset(shell->tokens, &shell->envvars);
	else if (ft_strcmp(shell->tokens[0]->cmd, "env") == 0)
		print_env(shell->envvars);
	else if (shell->tokens[0] != NULL)
		handle_command(shell->tokens);
	// if (shell->tokens != NULL)
	// 	free_tokens(shell->tokens);
	free(shell->input);
	return ;
}
