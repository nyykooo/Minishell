/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:01:30 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/27 14:33:54 by ncampbel         ###   ########.fr       */
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

// t_arg	*temp;
// 	int		arg_count;

// 	arg_count = 0;
// 	temp = command->arguments;
// 	while (temp->next)
// 	{
// 		if (arg_count > 1)
// 		{
// 			printf("too many arguments\n");
// 		}
// 		if (!is_number(temp->arg) || ! long_number(temp->arg))
// 		{
// 			printf("numeric argument required\n");
// 		}
// 		arg_count++;
// 		temp = temp->next;
// 	}
// 	return (0);

static int	analyze_exit_arguments(t_cmd *command)
{
	if (!command->arguments)
		return (0);
	if (!is_number(command->arguments->arg)
		|| !long_number(command->arguments->arg))
	{
		perror("exit: numeric argument required");
		return (2);
	}
	else if (command->arguments->arg)
	{
		if (command->arguments->next)
		{
			perror("exit: too many arguments");
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
