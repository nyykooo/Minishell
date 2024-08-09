/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/09 11:32:51 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

int	ft_handle_no_equal(t_minishell *shell, t_arg *argument)
{
	t_var	*temp;
	t_var	*new_var;

	temp = ft_find_envvar(shell->envvars, argument->arg);
	if (temp != NULL)
	{
		temp->exp = true;
		temp->env = true;
		return (0);
	}
	new_var = ft_calloc(1, sizeof(t_var));
	if (new_var == NULL)
		ft_print_error(true, 2, 1,
			"-minishell: failed to allocate memory\n");
	new_var->content = ft_strdup(argument->arg);
	new_var->name = ft_strdup(argument->arg);
	new_var->exp = true;
	ft_varadd_back(&shell->envvars, new_var);
	return (0);
}

bool	ft_handle_with_equal(t_minishell *shell, t_arg *argument)
{
	char	*name;
	char	*value;
	t_var	*var;
	int		equal_pos;

	equal_pos = ft_find_char(argument->arg, EQUAL);
	if (equal_pos == -1)
		return (false);
	name = ft_strndup(argument->arg, equal_pos);
	value = ft_strdup(argument->arg + equal_pos + 1);
	var = ft_find_envvar(shell->envvars, name);
	if (var != NULL)
	{
		free(var->value);
		var->value = ft_strdup(value);
	}
	else
		ft_add_new_envvar(&shell->envvars, name, value, 1);
	free(name);
	free(value);
	return (true);
}

bool	ft_check_options(t_arg *argument)
{
	char	*error_msg;

	if (argument->arg[0] == '-')
	{
		error_msg = ft_substr(argument->arg, 0, 2);
		ft_print_error(false, 2, 3,
			"-minishell: export: ", error_msg, ": invalid option\n");
		free(error_msg);
		return (true);
	}
	return (false);
}

int	ft_handle_export(t_minishell *shell)
{
	t_var	*current;
	t_arg	*temp;
	t_arg	*temp2;

	temp2 = shell->commands->arguments;
	while (temp2 != NULL)
		temp2 = temp2->next;
	if (!shell->commands)
		return (1);
	temp = shell->commands->arguments;
	if (temp == NULL)
	{
		current = shell->envvars;
		ft_sort_content(current);
		while (current != NULL)
		{
			ft_print_export(current);
			current = current->next;
		}
		return (0);
	}
	else
		return (ft_ft_handle_export_args(shell));
}
