/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/16 17:59:51 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

volatile sig_atomic_t	g_sig;

static char	*get_pathname(void)
{
	int		i;
	char	*substr;
	char	*result;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	while ((pwd)[i] != '\0')
		i++;
	while ((pwd)[--i] != '/')
		(void)pwd;
	if (i != 0)
		pwd[--i] = '~';
	substr = ft_substr(pwd, i, ft_strlen(pwd));
	result = ft_strjoin(substr, " $ ");
	if (substr)
		free(substr);
	if (pwd)
		free(pwd);
	return (result);
}

static bool	create_prompt(t_minishell *shell)
{
	char	*prompt;
	char	*input;

	prompt = get_pathname();
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		handle_exit(shell->commands, shell);
	if (input[0] == 0)
		return (false);
	if (input)
	{
		add_history(input);
		shell->input = ft_strdup(input);
		free(input);
	}
	return (true);
}

static void	clear_shell(t_minishell *shell)
{
	if (shell->tokens != NULL)
		free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
	if (shell->commands != NULL)
		free_commands(shell->commands);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->n_cmd = 0;
	shell->n_pipe = 0;
}

void	minishell_loop(t_minishell *shell)
{
	while (true)
	{
		if (create_prompt(shell))
		{
			analyze_input(shell);
			update_vars(shell);
			clear_shell(shell);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell	shell;

	g_sig = 0;
	(void)argv;
	if (argc != 1)
	{
		write(2, "usage: ./minishell\n", 20);
		return (EXIT_FAILURE);
	}
	config_signals(0);
	shell.envvars = create_list(envp);
	minishell_loop(&shell);
	free_var(shell.envvars); // a execucao nunca chega nessa linha?
	clear_history();
	return (0);
}
