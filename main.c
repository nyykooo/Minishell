/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:30:52 by ncampbel          #+#    #+#             */
/*   Updated: 2024/05/15 19:04:58 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "libs/headers.h"

static char	*ft_pathname(char *pwd)
{
	int	i;

	i = 0;
	while ((pwd)[i] != '\0')
		i++;
	while ((pwd)[i] != '/')
		i--;
	pwd[--i] = '~';
	return(ft_strjoin(ft_substr(pwd, i, ft_strlen(pwd)), " $ "));
}

int main(void)
{
	char *input;
	char *pwd;

	input = NULL;
	while (ft_strcmp(input, "exit") != 0)
	{
		pwd = getcwd(NULL, 0);
		pwd = ft_pathname(pwd);
		input = readline(pwd);
		add_history(input);
		free(pwd);
	}
	
	rl_clear_history();

    return (0);
}