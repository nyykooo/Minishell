/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 14:09:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/25 16:10:20 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

char **envvar_array(t_minishell *shell)
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
		env_var[++i] = ft_strdup(temp->content);
		temp = temp->next;
	}
	env_var[i] = NULL;
	return (env_var);
}

// juntar handle exec e handle commands na mesma funcao. o ./ é uma direção de caminho para o diretorio aual
// a função get_path do handle commands deve tentar abrir o arquivo cmd + 2, se nao conseguir, procura dentro da variavel de ambiente PATH
// se conseguir abrir o cmd + 2, o path da execve sera cmd + 2

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
