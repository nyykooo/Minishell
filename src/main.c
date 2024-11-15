/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/16 15:38:28 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

int	g_sig;

static char	*ft_get_pathname(void)
{
	int		i;
	char	*substr;
	char	*result;
	char	*pwd;

	i = 0;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (ft_strdup(" $ "));
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

static bool	ft_create_prompt(t_minishell *shell)
{
	char	*prompt;
	char	*input;

	prompt = ft_get_pathname();
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		ft_handle_exit(shell->commands, shell);
	if (input[0] == 0)
	{
		free(input);
		return (false);
	}
	if (input)
	{
		add_history(input);
		shell->input = ft_strdup(input);
		free(input);
	}
	return (true);
}

static void	ft_clear_shell(t_minishell *shell)
{
	if (shell->tokens != NULL)
		ft_free_tokens(shell->tokens);
	if (shell->input != NULL)
		free(shell->input);
	if (shell->commands != NULL)
		ft_free_commands(shell->commands);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->n_cmd = 0;
	shell->n_pipe = 0;
}

static void	ft_minishell_loop(t_minishell *shell)
{
	while (true)
	{
		if (ft_create_prompt(shell))
		{
			ft_update_questionvar(shell);
			ft_analyze_input(shell);
			ft_clear_shell(shell);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	*shell;

	if (argc != 1)
	{
		write(2, "usage: ./minishell\n", 20);
		return (EXIT_FAILURE);
	}
	shell = ft_get_shell();
	g_sig = 0;
	(void)argv;
	ft_config_signals(0);
	shell->envvars = ft_create_envvar_list(envp);
	ft_minishell_loop(shell);
	return (0);
}
