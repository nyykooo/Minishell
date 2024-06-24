/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:01:30 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/24 10:43:49 by ncampbel         ###   ########.fr       */
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

static int	analyze_exit_arguments(t_cmd *command)
{
	if (!command->arguments)
		return (0);
	if (command->arguments->next)
	{
		perror("exit: too many arguments");
		return (1);
	}
	else if (command->arguments->arg)
	{
		if (!is_number(command->arguments->arg)
			|| !long_number(command->arguments->arg))
		{
			perror("exit: numeric argument required");
			return (2);
		}
		else
			return (exit_number_analyze(command->arguments->arg));
	}
	return (0);
}

void	handle_exit(t_cmd *command, t_minishell *shell)
{
	if (command)
		shell->exit_status = analyze_exit_arguments(command);
	else
		shell->exit_status = 0;
	free_shell(shell);
	printf("exit\n");
	exit(shell->exit_status);
}
