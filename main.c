/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/23 22:15:04 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/headers.h"

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
    pwd[--i] = '~';
    substr = ft_substr(pwd, i, ft_strlen(pwd));
    result = ft_strjoin(substr, " $ ");
    free(substr);
	free(pwd);
    return result;
}
void	minishell_loop(t_envvar *envvar_list)
{
	char	*pwd;
	char	*input;

	input = NULL;
	pwd = NULL;
	while (ft_strcmp(input, "exit") != 0)
	{
		pwd = getcwd(NULL, 0);
		pwd = ft_pathname(pwd);
		input = readline(pwd);
		free(pwd);
		analyze_input(input, &envvar_list);
		if (input == NULL) // O Ctrl + D para a readline eh um NULL 
		{
			// Input tbm sera NULL quando ocorrer um erro, bora tratar isso
			break ;
		}
		add_history(input);
	}
	if (input != NULL)
        free(input);
}

t_envvar *create_list(char **envp)
{
	char	**current;
	t_envvar	*new_node;
	t_envvar	*head;
	t_envvar	*tail;

	head = NULL;
	tail = NULL;
	current = envp;
	while (*current)
	{
		new_node = malloc(sizeof(t_envvar));
		new_node->content = ft_strdup(*current);
		new_node->next = NULL;
		if (head == NULL)
			head = new_node;
		else
			tail->next = new_node;
		current++;
		tail = new_node;
	}
	return (head);
}

void	free_list(t_envvar *head)
{
	t_envvar	*current;
	t_envvar	*next;

	current = head;
	while (current)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envvar	*envvar_list;

	(void)argv;
	if (argc != 1)
	{
		write(2, "usage: ./minishell\n", 20);
		return (EXIT_FAILURE);
	}
	envvar_list = NULL;
	envvar_list = create_list(envp);
	minishell_loop(envvar_list);
	printf("exit\n");
	free_list(envvar_list);
	clear_history();
	return (0);
}
