/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/28 12:17:21 by brunhenr         ###   ########.fr       */
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

/*static void	pipe_redir_hub(t_minishell *shell)
{
	t_cmd	*cmd;
	
	cmd = shell->commands;
	while (cmd)
	{
		if (cmd->type == T_PIPE)
			printf("im a pipe\n");
		else if (cmd->type >= T_RTRUNC && cmd->type <= T_LAPEND)
			// handle_redir(cmd, shell);
			printf("im a redir\n)");
		else
			handle_builtins(shell);
		cmd = cmd->next;
	}
}*/
int is_builtin(t_cmd *cmd)
{
	int	i;
    const char *builtins[] = {"cd", "exit", "export", "unset", "echo", NULL};

	i = 0;
    while (builtins[i] != NULL)
	{
		if(cmd->cmd != NULL)
		{
        	if (strcmp(cmd->cmd, builtins[i]) == 0)
            	return 1; // É um built-in
        }
		i++;
    }
    return 0; // Não é um built-in
}

/*void config_output_redirection(t_cmd *cmd)
{
	int	fd_out;
	char	*error_msg;
	t_cmd	*last_cmd;
	
	last_cmd = cmd;
	// Encontrar o último comando de redirecionamento
	while (last_cmd->next != NULL && (last_cmd->next->rtrunc || last_cmd->next->rappend))
	{
		last_cmd = last_cmd->next;
	}

	// Configurar redirecionamento baseado no último comando de redirecionamento encontrado
	if (last_cmd->path != NULL) {
		int flags = O_WRONLY | O_CREAT | (last_cmd->rtrunc ? O_TRUNC : O_APPEND);
		fd_out = open(last_cmd->path, flags, 0644);
		if (fd_out < 0) {
			error_msg = error_msg_construct(4, "-minishell: ", last_cmd->path, ": ", strerror(errno));
			put_error_msg(error_msg, fd_out); // Ajustar o EXIT_STATUS aqui
			free(error_msg);
			exit(EXIT_FAILURE);
		}
		dup2(fd_out, STDOUT_FILENO);
		close(fd_out);
	}
}*/
// testar ficheiro com pipe
// testar pipeline com ficheiro sem permissoes = o retorno sera: permissoes negados
// o retorno da open devido a falta de permissao eh < 0?
/*void	config_output_redirection(t_cmd *cmd)
{
	int		fd_out;
	char	*error_msg;

	if (cmd->path != NULL)
	{
		if (cmd->next->rtrunc)
		{
			fd_out = open(cmd->next->path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0)
			{
				error_msg = error_msg_construct(4, "-minishell: ", cmd->next->path, ": ", strerror(errno));
				put_error_msg(error_msg, fd_out); //corrigir o EXIT_STATUS aqui
				free(error_msg);
				exit(EXIT_FAILURE);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (cmd->next->rappend)
		{
			fd_out = open(cmd->next->path, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out < 0)
			{
				error_msg = error_msg_construct(4, "-minishell: ", cmd->next->path, ": ", strerror(errno));
				put_error_msg(error_msg, fd_out); //corrigir o EXIT_STATUS aqui
				free(error_msg);
				exit(EXIT_FAILURE);
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
	}
}*/

void	analyze_input(t_minishell *shell)
{
	t_cmd	*temp;
	parsing_hub(shell);
	temp = shell->commands;
	while (temp)
	{
		printf("temp->cmd: %s\n", temp->cmd);
		printf("temp->type: %d\n", temp->type);
		printf("temp->rtrunc: %d\n", temp->rtrunc);
		printf("temp->rappend: %d\n", temp->rappend);
		printf("temp->lappend: %d\n", temp->lappend);
		printf("temp->ltrunc: %d\n", temp->ltrunc);
		temp = temp->next;
	}
	exit(0);
	// pensar em um loop para percorrer varios comandos relacionando com a quantidade de pipes e redirects
	if (shell->n_cmd > 1)
	{
		handle_pipe(shell->commands);
		//pipe_redir_hub(shell);
	}
	else if (shell->commands)
	{
		if (shell->commands->type == T_EQUAL)
			handle_equal(shell, shell->commands);
		if (shell->commands->type == T_COMMAND)
			handle_builtins(shell);
	}
	return ;
}