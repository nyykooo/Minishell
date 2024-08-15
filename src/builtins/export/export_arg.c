/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 22:20:03 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/15 21:01:17 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static bool	ft_verify_equal_arg(const char *arg)
{
	int		i;
	bool	before_equal;

	before_equal = true;
	i = 0;
	while (arg[i] != EQUAL || before_equal)
	{
		if (arg[i] != '_' && !(arg[i] >= 'A' && arg[i] <= 'Z')
			&& !(arg[i] >= 'a' && arg[i] <= 'z') && !(arg[i] >= '0'
				&& arg[i] <= '9') && arg[i] != '\\')
			return (false);
		if (arg[++i] == EQUAL)
			before_equal = false;
	}
	return (true);
}

static bool	ft_verify_noequal_arg(const char *arg)
{
	int		i;

	i = 0;
	while (arg[++i] != 0)
	{
		if (arg[i] != '_' && !(arg[i] >= 'A' && arg[i] <= 'Z')
			&& !(arg[i] >= 'a' && arg[i] <= 'z') && !(arg[i] >= '0'
				&& arg[i] <= '9') && arg[i] != '\\')
			return (false);
	}
	return (true);
}

static bool	ft_is_valid_arg(const char *arg, bool has_equal)
{
	bool	return_value;

	return_value = true;
	if ((arg[0] >= '0' && arg[0] <= '9'))
		return (false);
	if (has_equal)
		return_value = ft_verify_equal_arg(arg);
	else
		return_value = ft_verify_noequal_arg(arg);
	return (return_value);
}

int	ft_handle_export_args(t_minishell *shell)
{
	t_arg	*temp;

	temp = shell->commands->arguments;
	while (temp != NULL)
	{
		if (ft_check_options(temp))
			return (shell->exit_status);
		if (temp->arg[0] == '_' && temp->arg[1] == '=')
			return (0);
		if (!ft_is_valid_arg(temp->arg, temp->equal))
			ft_print_error(false, 1, 3, "-minishell: export: `",
				temp->arg, "': not a valid identifier\n");
		else
		{
			if (temp->equal == false)
				shell->exit_status = ft_handle_no_equal(shell, temp);
			else
				ft_handle_with_equal(shell, temp);
		}
		temp = temp->next;
	}
	return (shell->exit_status);
}
