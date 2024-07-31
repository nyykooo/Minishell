/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/07/31 17:10:39 by ncampbel         ###   ########.fr       */
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
			i = 0;
			while (dirs[i] != NULL)
				free(dirs[i++]);
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

static void	ft_get_path(t_cmd *commands)
{
	if (access(commands->cmd, X_OK) != 0)
		commands->path = get_command_path(commands->cmd);
	else
		commands->path = ft_strdup(commands->cmd);
}

static void	handle_command(t_cmd *commands, t_minishell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_analyze_cmd(commands);
	else if (pid < 0)
		perror ("minishell");
	else
		waitpid (pid, &(shell->exit_status), WUNTRACED);
	if (WIFEXITED(shell->exit_status))
		shell->exit_status = WEXITSTATUS(shell->exit_status);
}

static void	handle_builtins(t_minishell *shell)
{
		ft_get_path(shell->commands);
		ft_update_underlinevar(shell);
		if (ft_strcmp(shell->commands->cmd, "cd") == 0)
			handle_cd(shell->commands, shell);
		else if (ft_strcmp(shell->commands->cmd, "echo") == 0)
			handle_echo(shell->commands);
		else if (ft_strcmp(shell->commands->cmd, "exit") == 0)
			handle_exit(shell->commands, shell);
		else if (ft_strcmp(shell->commands->cmd, "export") == 0)
			shell->exit_status = handle_export(shell);
		else if (ft_strcmp(shell->commands->cmd, "unset") == 0)
			handle_unset(shell->commands, &shell->envvars);
		else if (ft_strcmp(shell->commands->cmd, "env") == 0)
			handle_env(shell->envvars, shell, shell->commands);
		else if (ft_strcmp(shell->commands->cmd, "pwd") == 0)
			handle_pwd(shell);
		else if (shell->commands != NULL)
			handle_command(shell->commands, shell);
		free(shell->commands->path);
}

void	ft_analyze_input(t_minishell *shell)
{
	//t_cmd *temp;
	//t_arg *temp_arg;
	int	status;
	
	status = 0;
	parsing_hub(shell);
	if (shell->n_cmd == 0)
		return ;
	status = heredoc(shell);
	/*printf("status: %d\n", status);
	printf("WIFEXITED: %d\n", WIFEXITED(status));
	if (WIFEXITED(status))
		printf("WEXITSTATUS: %d\n", WEXITSTATUS(status));
	printf("WIFSIGNALED: %d\n", WIFSIGNALED(status));
	if (WIFSIGNALED(status))
		printf("WTERMSIG: %d\n", WTERMSIG(status));*/
	if (WIFEXITED(status) == true && WEXITSTATUS(status) == 8)
			return ;
	/*temp = shell->commands;
	printf("NUMERO DE CMDS: %d\n", shell->n_cmd);
	while (temp)
	{
		printf("temp->cmd: %s\n", temp->cmd);
		printf("temp->type: %d\n", temp->type);
		printf("temp->rtrunc: %d\n", temp->rtrunc);
		printf("temp->rappend: %d\n", temp->rappend);
		printf("temp->lappend: %d\n", temp->lappend);
		printf("temp->input_file: %d\n", temp->input_file);
		printf("temp->path: %s\n", temp->path);
		printf("temp->here_doc_fd: %d\n", temp->here_doc_fd);
		temp_arg = temp->arguments;
		while (temp_arg)
		{
			printf("temp->arguments->arg: %s\n", temp_arg->arg);
			temp_arg = temp_arg->next;
		}
		printf("----------------\n");
		temp = temp->next;
	}*/
	if (shell->n_cmd > 1 || (ft_strcmp(shell->commands->cmd, ">") == 0)) //Isso implica que temos |, &&, ||, ;, (), {}. Ou merameante <, >, >>, <<.
		handle_pipe_and_redir(shell, shell->commands);
	else if (shell->commands)
	{
		if (shell->commands->type == T_EQUAL)
			ft_handle_equal(shell, shell->commands);
		if (shell->commands->type == T_COMMAND)
			handle_builtins(shell);
	}
	return ;
}
