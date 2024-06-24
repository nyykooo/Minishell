/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:01:30 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/24 00:48:35 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static bool	long_number(const char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (nbr[i] == '-' || nbr[i] == '+')
			i++;
		while (nbr[i] == '0')
			i++;
		if (ft_strlen(nbr + i) >= 19)
			return (false);
		else
			return (true);
	}
	return (true);
}

static int	negative_to_binary(int negative)
{
	unsigned int	num;

	num = (unsigned int)negative;
	return (num);
}

static bool is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

static int	exit_number_analyze(char *arg)
{
	int	number;

	number = ft_atoi(arg);
	if (number < 0)
		return (negative_to_binary(number));
	else if (number >= 0 && number <= 255)
		return (number);
	else
		return (number % 256);
		
}

static int	analyze_exit_arguments(t_minishell *shell)
{
	if (shell->commands->arguments->next)
	{
		perror("exit: too many arguments");
		return (1);
	}
	else if (shell->commands->arguments->arg)
	{
		if (!is_number(shell->commands->arguments->arg)
			|| !long_number(shell->commands->arguments->arg))
		{
			perror("exit: numeric argument required");
			return (2);
		}
		else
			return (exit_number_analyze(shell->commands->arguments->arg));
	}
	return (0);
}

void	handle_exit(t_minishell *shell)
{
	shell->exit_status = analyze_exit_arguments(shell);
	free_shell(shell);
	printf("exit\n");
	exit(shell->exit_status);
}
