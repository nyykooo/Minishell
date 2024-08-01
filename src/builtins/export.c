/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/01 16:26:48 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

bool	is_valid_arg(const char *arg, bool has_equal)
{
	int	i;

	i = 0;
	if (has_equal == true)
	{
		while (arg[i] != '=')
		{
			if (arg[i] == '-')
				return (false);
			i++;
		}
	}
	else if (has_equal == false)
	{
		while (arg[i] != '\0')
		{
			if (arg[i] == '-')
				return (false);
			i++;
		}
	}
	return (arg[0] == '_' || (arg[0] >= 'A' && arg[0] <= 'Z') || \
	(arg[0] >= 'a' && arg[0] <= 'z'));
}

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
		return (1);
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
	int		i;

	equal_pos = -1;
	i = 0;
	while (argument->arg[i] != '\0')
	{	
		if (argument->arg[i] == '=')
		{
			equal_pos = i;
			break ;
		}
		i++;
	}
	if (equal_pos == -1)
		return (1);
	name = ft_strndup(argument->arg, equal_pos);
	value = ft_strdup(argument->arg + equal_pos + 1);
	var = shell->envvars;
	while (var != NULL)
	{
		if (strcmp(var->name, name) == 0)
		{
			free(var->value);
			var->value = value;
			free(name);
			return (0);
		}
		var = var->next;
	}
	var = malloc(sizeof(t_var));
	if (!var)
	{
		free(name);
		free(value);
		return (1);
	}
	var->name = name;
	var->value = value;
	var->env = true;
	var->exp = true;
	var->content = ft_create_envvar_content(name, value);
	var->next = shell->envvars;
	shell->envvars = var;
	return (0);
}

static int	handle_export_args(t_minishell *shell)
{
	t_arg	*temp;
	int		exit_status;
	char	*error_msg;

	exit_status = 0;
	temp = shell->commands->arguments;
	while (temp != NULL)
	{
		if (temp->arg[0] == '_' && temp->arg[1] == '=')
			return (0);
		if (is_valid_arg(temp->arg, temp->equal) == false)
		{
			// ft_print_error_and_free(shell, false, 1, 3, "-minishell: export: ", temp->arg, ": not a valid identifier\n");
			error_msg = error_msg_construct(3, "-minishell: export: ", temp->arg, ": not a valid identifier\n");
			exit_status = put_error_msg(error_msg, 1);
		}
		else
		{
			if (temp->equal == false)
				exit_status = handle_no_equal(shell, temp);
			else
				handle_with_equal(shell, temp);
		}
		temp = temp->next;
	}
	return (exit_status);
}

void	swap_nodes(t_var *a, t_var *b)
{
	char *temp_content;
	char *temp_name;
	char *temp_value;
	bool temp_exp;
	bool temp_env;
	
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
	int swapped = 1;
    t_var *temp;
    t_var *last_verified = NULL;

    if (envvar == NULL)
        return;

    while (swapped) {
        swapped = 0;
        temp = envvar;

        while (temp->next != last_verified) {
            if (ft_strcmp(temp->content, temp->next->content) > 0) { 
                swap_nodes(temp, temp->next);
                swapped = 1;
            }
            temp = temp->next;
        }
        last_verified = temp;
    }
}

static char *prepare_value(char *content)
{
	char	*value;
	int		i;
	int		j;
	int		count_meta;

	i = -1;
	count_meta = 0;
	while (content[++i] != '\0')
	{
		if (content[i] == '\"' || content[i] == '\\' || content[i] == '$' || content[i] == '`')
			count_meta++;
	}
	value = malloc(sizeof(char)*(ft_strlen(content) + count_meta + 1));
	if (value == NULL)
		return (NULL);
	i = -1;
	j = 0;
	while (content[++i] != '\0')
	{
		if (content[i] == '\"' || content[i] == '\\' || content[i] == '$' || content[i] == '`')
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
