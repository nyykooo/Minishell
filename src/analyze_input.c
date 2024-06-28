/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:56:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/28 10:31:06 by brunhenr         ###   ########.fr       */
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
	t_cmd *cmd;
	t_cmd *temp;

	parsing_hub(shell);
	cmd = shell->commands;
	temp = shell->commands;
	while (temp != NULL)
	{
		printf("temp->cmd: %s\n", temp->cmd);
		printf("temp->type: %d\n", temp->type);
		printf("temp->rapend: %d\n", temp->rappend);
		printf("temp->rtrunc: %d\n", temp->rtrunc);
		printf("temp->ltrunc: %d\n", temp->ltrunc);
		temp = temp->next;
	}
	exit(0);
	int fd_in, fd_out; // fds para redirecionamento de in e out
	int pipefd[2]; // File descriptors para pipes
	int last_in = 0; // Guarda o read end do último pipe

	while (cmd != NULL)
	{
		if (cmd->type == T_COMMAND && is_builtin(cmd))
		{
			// VER ISSO: cd nao pode ser executado em um processo filho
			//config_output_redirection(cmd);
			handle_builtins(shell);
			cmd = cmd->next;
			continue;
		}
		// Configura redirecionamento de entrada
		if (cmd->redirect_in)
		{
			fd_in = open(cmd->redirect_in, O_RDONLY);
			if (fd_in < 0)
			{
				perror("Erro ao abrir arquivo de entrada");
				return;
			}
			dup2(fd_in, STDIN_FILENO);
			close(fd_in);
		}
		else if (last_in != 0)
		{
			// Se não há redirecionamento de entrada, mas estamos em um pipe
			dup2(last_in, STDIN_FILENO);
			close(last_in);
		}
		// Configura redirecionamento de saída, append ou pipe
		if (cmd->next && cmd->next->type == T_PIPE)
		{
			pipe(pipefd);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			last_in = pipefd[0]; // Prepara o read end para o próximo comando
		}
		else if (cmd->redirect_out)
		{
			// Trata redirecionamento de saída
			fd_out = open(cmd->redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out < 0) {
				perror("Erro ao abrir arquivo de saída");
				return;
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		else if (cmd->redirect_append)
		{
			// Trata redirecionamento de saída com append
			fd_out = open(cmd->redirect_append, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out < 0) {
				perror("Erro ao abrir arquivo de saída para append");
				return;
			}
			dup2(fd_out, STDOUT_FILENO);
			close(fd_out);
		}
		// Executa o comando se não for um built-in
		if (cmd->type == T_COMMAND)
		{
			handle_command(cmd, shell);
		}
		// Restaura os descritores padrão e avança para o próximo comando
		dup2(STDIN_FILENO, 0);
		dup2(STDOUT_FILENO, 1);
		cmd = cmd->next;
	}
}
	
/*void	analyze_input(t_minishell *shell)
{
	t_cmd *cmd;
	t_cmd *temp;

	parsing_hub(shell);
	temp = shell->commands;
	printf("n_cmd: %d\n", shell->n_cmd);
	while (temp != NULL)
	{
		printf("temp->cmd: %s\n", temp->cmd);
		printf("temp->type: %d\n", temp->type);
		temp = temp->next;
	}
	if (shell->n_cmd > 1)
	{
		cmd = shell->commands;
		while (cmd != NULL)
		{
			if (cmd->type == T_COMMAND)
			{
				if (cmd->next && cmd->next->type == T_PIPE)
				{
					handle_pipe(cmd);
					break;
				}
				else
					handle_builtins(shell); // Lida com um comando simples ou o último comando antes de um pipe
			}
			// Add mais condições conforme necessário para outros tipos de comandos e redir
			cmd = cmd->next;
		}
	}
	else if (shell->n_cmd == 1 && shell->commands)
	{
		handle_command(shell->commands, shell);
	}
	// tratar, por exemplo, nenhum comando ou apenas redirecionamentos
}

void	analyze_input(t_minishell *shell)
{
	parsing_hub(shell);
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
}*/
