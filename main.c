/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/17 18:38:23 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/headers.h"

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
		pwd = getcwd(NULL, 0);
		pwd = ft_pathname(pwd);
		input = readline(pwd);
		analyze_input(input);
		if (input == NULL) // O Ctrl + D para a readline eh um NULL 
		{
			// Input tbm sera NULL quando ocorrer um erro, bora tratar isso
			free(pwd);
			break ;
		}
		add_history(input);
		free(pwd);
	}
	free(input);
	rl_clear_history();
	return (0);
}
