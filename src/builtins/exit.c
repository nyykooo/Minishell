/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:01:30 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/01 16:27:07 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

static bool	long_number(const char *nbr)
{
	int	i;
	int	j;
	char *new_nbr;

	i = 0;
	j = 0;
	new_nbr = (char *)malloc(sizeof(char) * (ft_strlen(nbr) + 1));
	while (nbr[i] == ' ')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i] == '0')
		i++;
	while (ft_isdigit(nbr[i]))
		new_nbr[j++] = nbr[i++];
	new_nbr[j] = '\0';
	if (ft_strlen(new_nbr) >= 19)
	{
		free(new_nbr);
		return (false);
	}
	free(new_nbr);
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
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (false);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			while (str[i] == ' ')
				i++;
			if (str[i] == '\0')
				return (true);
			else
				return (false);
		}
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
	char *error_msg;	

	if (!command->arguments)
		return (0);
	if (!is_number(command->arguments->arg)
		|| !long_number(command->arguments->arg))
	{
		// ft_print_error_and_free(command->shell, false, 2, 3, "-minishell: exit: ", command->arguments->arg,
		// 	 ": numeric argument required\n");
		error_msg = error_msg_construct(3, "-minishell: exit: ", command->arguments->arg, ": numeric argument required\n");
		put_error_msg(error_msg, 2);
		return (2);
	}
	else if (command->arguments->arg)
	{
		if (command->arguments->next)
		{
			// ft_print_error_and_free(command->shell, false, 1, 1, "-minishell: exit: too many arguments\n");
			error_msg = error_msg_construct(1, "-minishell: exit: too many arguments\n");
			put_error_msg(error_msg, 1);
			return (1);
		}
		else
			return (exit_number_analyze(command->arguments->arg));
	}
	return (0);
}

void	handle_exit(t_cmd *command, t_minishell *shell)
{
	printf("exit\n");
	if (command)
		shell->exit_status = analyze_exit_arguments(command);
	else
		shell->exit_status = 0;
	free_shell(shell);
	exit(shell->exit_status);
}
