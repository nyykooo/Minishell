/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/05 17:24:57 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

bool	ft_check_options(t_minishell *shell, t_arg *argument)
{
	char	*error_msg;

	if (argument->arg[0] == '-')
	{
		error_msg = ft_substr(argument->arg, 0, 2);
		ft_print_error(shell, false, 2, 3,
			"-minishell: export: ", error_msg, ": invalid option\n");
		free(error_msg);
		return (true);
	}
	return (false);
}

static bool	ft_is_valid_arg(const char *arg, bool has_equal)
{
	int		i;
	bool	before_equal;

	i = 0;
	before_equal = true;
	if ((arg[0] >= '0' && arg[0] <= '9'))
		return (false);
	if (has_equal)
	{
		while (arg[i] != EQUAL || before_equal)
		{
			if (arg[i] != '_' && !(arg[i] >= 'A' && arg[i] <= 'Z')
				&& !(arg[i] >= 'a' && arg[i] <= 'z') && !(arg[i] >= '0' && arg[i] <= '9') && arg[i] != '\\')
				return (false);
			if (arg[++i] == EQUAL)
				before_equal = false;
		}
	}
	if (!has_equal)
	{
		while (arg[++i] != 0)
		{
			if (arg[i] != '_' && !(arg[i] >= 'A' && arg[i] <= 'Z')
				&& !(arg[i] >= 'a' && arg[i] <= 'z') && !(arg[i] >= '0' && arg[i] <= '9') && arg[i] != '\\')
				return (false);
		}
	}
	return (true);
}

// bool	is_valid_arg(const char *arg, bool has_equal)
// {
// 	int	i;

// 	i = 0;
// 	if (has_equal == true)
// 	{
// 		while (arg[i] != '=')
// 		{
// 			if (arg[i] == '-')
// 				return (false);
// 			i++;
// 		}
// 	}
// 	else if (has_equal == false)
// 	{
// 		while (arg[i] != '\0')
// 		{
// 			if (arg[i] == '-')
// 				return (false);
// 			i++;
// 		}
// 	}
// 	return (arg[0] == '_' || (arg[0] >= 'A' && arg[0] <= 'Z') || 
// 	(arg[0] >= 'a' && arg[0] <= 'z'));
// }

static int	handle_no_equal(t_minishell *shell, t_arg *argument)
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
		ft_print_error(shell, true, 2, 1,
			"-minishell: failed to allocate memory\n");
	new_var->content = ft_strdup(argument->arg);
	new_var->name = ft_strdup(argument->arg);
	new_var->exp = true;
	ft_varadd_back(&shell->envvars, new_var);
	return (0);
}

static bool	handle_with_equal(t_minishell *shell, t_arg *argument)
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
		var->value = value;
		free(name);
	}
	else
		ft_add_new_envvar(&shell->envvars, name, value, 0);
	return (0);
}

static int	handle_export_args(t_minishell *shell)
{
	t_arg	*temp;

	temp = shell->commands->arguments;
	while (temp != NULL)
	{
		if (ft_check_options(shell, temp))
			return (shell->exit_status);
		if (temp->arg[0] == '_' && temp->arg[1] == '=')
			return (0);
		if (!ft_is_valid_arg(temp->arg, temp->equal))
			ft_print_error(shell, false, 1, 3, "-minishell: export: ",
				temp->arg, ": not a valid identifier\n");
		else
		{
			if (temp->equal == false)
				shell->exit_status = handle_no_equal(shell, temp);
			else
				handle_with_equal(shell, temp);
		}
		temp = temp->next;
	}
	return (shell->exit_status);
}

void	swap_nodes(t_var *a, t_var *b)
{
	char	*temp_content;
	char	*temp_name;
	char	*temp_value;
	bool	temp_exp;
	bool	temp_env;

	temp_content = a->content;
	temp_name = a->name;
	temp_value = a->value;
	temp_exp = a->exp;
	temp_env = a->env;
	a->content = b->content;
	a->name = b->name;
	a->value = b->value;
	a->exp = b->exp;
	a->env = b->env;
	b->content = temp_content;
	b->name = temp_name;
	b->value = temp_value;
	b->exp = temp_exp;
	b->env = temp_env;
}

void	sort_content(t_var *envvar)
{
	t_var			*temp;
	t_var			*last_verified;
	int				swapped;

	swapped = 1;
	last_verified = NULL;
	if (envvar == NULL)
		return ;
	while (swapped)
	{
		swapped = 0;
		temp = envvar;
		while (temp->next != last_verified)
		{
			if (ft_strcmp(temp->content, temp->next->content) > 0)
			{
				swap_nodes(temp, temp->next);
				swapped = 1;
			}
			temp = temp->next;
		}
		last_verified = temp;
	}
}

static char	*prepare_value(char *content)
{
	char	*value;
	int		i;
	int		j;
	int		count_meta;

	i = -1;
	count_meta = 0;
	while (content[++i] != '\0')
	{
		if (content[i] == '\"' || content[i] == '\\'
			|| content[i] == '$' || content[i] == '`')
			count_meta++;
	}
	value = malloc(sizeof(char) * (ft_strlen(content) + count_meta + 1));
	if (value == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (content[++i] != '\0')
	{
		if (content[i] == '\"' || content[i] == '\\'
			|| content[i] == '$' || content[i] == '`')
			value[j++] = '\\';
		value[j++] = content[i];
	}
	value[j] = '\0';
	return (value);
}

// pensar sobre criar uma variadic function para montar a string que printa o export

int	handle_export(t_minishell *shell)
{
	t_var	*current;
	t_arg	*temp;
	t_arg	*temp2;
	char	*value;

	temp2 = shell->commands->arguments;
	while (temp2 != NULL)
		temp2 = temp2->next;
	if (!shell->commands)
		return (1);
	temp = shell->commands->arguments;
	if (temp == NULL)
	{
		current = shell->envvars;
		sort_content(current);
		while (current != NULL)
		{
			value = NULL;
			if (current->exp == true && current->env == true && \
			current->value != NULL)
			{
				value = prepare_value(current->value);
				printf("declare -x %s=\"%s\"\n", current->name, value);
			}
			else if (current->exp == true && current->value)
			{
				value = prepare_value(current->value);
				printf("declare -x %s=\"%s\"\n", current->name, value);
			}
			else if (current->exp == true && current->value == NULL)
				printf("declare -x %s\n", current->name);
			current = current->next;
			if (value)
				free(value);
		}
		return (0);
	}
	else
		return (handle_export_args(shell));
}
