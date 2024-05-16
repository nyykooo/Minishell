/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/17 00:29:58 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/headers.h"

static void	analyze_input(char *input)
{
	char	**commands;
	int		i;

	if (!input)
		return ;
	commands = ft_split(input, ' ');
	// commands = mega_parsing(input);
	if (ft_strcmp(commands[0], "cd") == 0)
	{
		if (chdir(commands[1]) == -1)
			write (2, "cd: no such file or directory\n", 30);
	}
	else if (commands[0] != NULL)
	{
		if (ft_strcmp(commands[0], "exit") != 0)
			write(2, "command not found\n", 18);
	}
	i = 0;
	while (commands[i] != NULL)
		free(commands[i++]);
	return ;
}

static char	*ft_pathname(char *pwd)
{
	int	i;

	i = 0;
	while ((pwd)[i] != '\0')
		i++;
	while ((pwd)[i] != '/')
		i--;
	pwd[--i] = '~';
	return (ft_strjoin (ft_substr(pwd, i, ft_strlen(pwd)), " $ "));
}

int	main(void)
{
	char	*input;
	char	*pwd;

	input = NULL;
	while (ft_strcmp(input, "exit") != 0)
	{
		analyze_input(input);
		pwd = getcwd(NULL, 0);
		pwd = ft_pathname(pwd);
		input = readline(pwd);
		add_history(input);
		free(pwd);
	}
	rl_clear_history();
	return (0);
}
