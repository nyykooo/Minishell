/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/08 11:02:04 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/headers.h"

volatile sig_atomic_t ctrl_c_pressed = 0;

static char	*ft_pathname(char *pwd)
{
    int	i;
    char *substr;
    char *result;

    i = 0;
    while ((pwd)[i] != '\0')
        i++;
    while ((pwd)[i] != '/')
        i--;
    if (&pwd[i] != pwd)
		pwd[--i] = '~';
    substr = ft_substr(pwd, i, ft_strlen(pwd));
    result = ft_strjoin(substr, " $ ");
    free(substr);
	free(pwd);
    return result;
}

void	handle_sigint(int sig) 
{
	(void)sig;
	ctrl_c_pressed = 1;
	write(1, "^C", 3);

}

void	minishell_loop(t_minishell *shell)
{
	char	*pwd;
	char	*input;

	signal(SIGINT, handle_sigint);
	input = NULL;
	pwd = NULL;
	rl_catch_signals = 0; // uma var global do readline que impede o ctrl+c de ser capturado
	while (1)
	{
		pwd = getcwd(NULL, 0);
		pwd = ft_pathname(pwd);
		//edit_termios();
		input = readline(pwd);
		//printf("input: %s\n", input);
		free(pwd);
		if (ctrl_c_pressed)
		{
			ctrl_c_pressed = 0;
			continue ;
		}
		if (input == NULL)
			handle_exit(shell);
		if (input[0] != '\0')
			add_history(input);
		analyze_input(input, shell);
	}
	if (input != NULL)
        free(input);
}

t_var *create_list(char **envp)
{
	t_var	*new_node;
	t_var	*head;
	t_var	*tail;

	head = NULL;
	tail = NULL;
	while (*envp)
	{
		new_node = malloc(sizeof(t_var));
		new_node->content = ft_strdup(*envp);
		new_node->env = true;
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			tail->next = new_node;
		envp++;
		tail = new_node;
	}
	return (head);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell *shell;

	//edit_termios();
	shell = ft_calloc(1, sizeof(t_minishell));
	(void)argv;
	if (argc != 1)
	{
		write(2, "usage: ./minishell\n", 20);
		return (EXIT_FAILURE);
	}
	shell->envvars = create_list(envp);
	minishell_loop(shell);
	free_list(shell->envvars);
	clear_history();
	return (0);
}
