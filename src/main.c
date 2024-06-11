/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/11 20:52:58 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

static char	*get_pathname(void)
{
    int	i;
    char *substr;
    char *result;
	char *pwd;

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
    return result;
}

static bool create_prompt(t_minishell *shell)
{
	char	*prompt;
	char	*input;

	input = NULL;
	prompt = get_pathname();
	input = readline(prompt);
	free(prompt);
	if (input == NULL)
		handle_exit(shell); //gostaria de diferenciar o ctrl + D do erro
	if (input[0] == 0)
		return (false);
	add_history(input);
	shell->input = ft_strdup(input);
	if (input != NULL)
        free(input);
	return (true);
}

static void clear_shell(t_minishell *shell)
{
	free(shell->input);
}

void	minishell_loop(t_minishell *shell)
{
	while (true)
	{
		if (create_prompt(shell))
		{
			analyze_input(shell);
			clear_shell(shell);
		}
	}
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	//g_value = 130;
}

int	main(int argc, char **argv, char **envp)
{
	static t_minishell shell;

	(void)argv;
	if (argc != 1)
	{
		write(2, "usage: ./minishell\n", 20);
		return (EXIT_FAILURE);
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	shell.envvars = create_list(envp);
	minishell_loop(&shell);
	free_var(shell.envvars);
	clear_history();
	return (0);
}
