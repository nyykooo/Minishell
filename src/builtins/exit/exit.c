/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:01:30 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 11:33:38 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static bool	ft_isnt_limits(const char *nbr)
{
	if (ft_strlen(nbr) >= 19)
	{
		if (ft_strcmp(nbr, "9223372036854775807") == 0)
			return (true);
		else if (ft_strcmp(nbr, "-9223372036854775808") == 0)
			return (true);
		return (false);
	}
	return (true);
}

static bool	ft_long_number(const char *nbr)
{
	int		i;
	int		j;
	char	*new_nbr;

	i = 0;
	j = 0;
	new_nbr = (char *)malloc(sizeof(char) * (ft_strlen(nbr) + 1));
	while (nbr[i] == ' ')
		i++;
	if (nbr[i] == '-' || nbr[i] == '+')
		new_nbr[j++] = nbr[i++];
	while (nbr[i] == '0')
		i++;
	while (ft_isdigit(nbr[i]))
		new_nbr[j++] = nbr[i++];
	new_nbr[j] = '\0';
	if (!ft_isnt_limits(new_nbr))
	{
		free(new_nbr);
		return (false);
	}
	free(new_nbr);
	return (true);
}

static int	exit_number_analyze(char *arg)
{
	int	number;

	number = ft_atoi(arg);
	if (number < 0)
		return (ft_itoui(number));
	else if (number >= 0 && number <= 255)
		return (number);
	else
		return (number % 256);
}

static int	ft_analyze_exit_arguments(t_cmd *command)
{
	if (!command->arguments)
		return (0);
	if (!ft_is_number(command->arguments->arg)
		|| !ft_long_number(command->arguments->arg))
	{
		ft_print_error(false, 2, 3, "-minishell: exit: ",
			command->arguments->arg, ": numeric argument required\n");
		return (2);
	}
	else if (command->arguments->arg)
	{
		if (command->arguments->next)
		{
			ft_print_error(false, 1, 1,
				"-minishell: exit: too many arguments\n");
			return (1);
		}
		else
			return (exit_number_analyze(command->arguments->arg));
	}
	return (0);
}

void	ft_handle_exit(t_cmd *command, t_minishell *shell)
{
	if (command)
		shell->exit_status = ft_analyze_exit_arguments(command);
	else
		shell->exit_status = 0;
	if (shell->exit_status == 2 || shell->exit_status == 1)
		return ;
	ft_free_shell(shell);
	exit(shell->exit_status);
}
