/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:33:57 by brunhenr          #+#    #+#             */
/*   Updated: 2024/06/26 17:46:02 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

bool	is_valid_arg(const char *arg)
{
	return (arg[0] == '_' || (arg[0] >= 'A' && arg[0] <= 'Z') || \
	(arg[0] >= 'a' && arg[0] <= 'z'));
}

static int	handle_no_equal(t_minishell *shell, t_arg *argument)
{
	t_var	*temp;
	t_var	*new_var;

	temp = find_envvar(shell->envvars, argument->arg);
	if (temp != NULL)
	{
		temp->exp = true;
		temp->env = true;
		return (0);
	}
	new_var = ft_calloc(1, sizeof(t_var));
	if (new_var == NULL)
		return (1);
	new_var->content = strdup(argument->arg);
	new_var->name = strdup(argument->arg);
	new_var->exp = true;
	ft_varadd_back(&shell->envvars, new_var);
	return (0);
}

// static int	handle_no_equal(t_minishell *shell, t_arg *argument)
// {
// 	t_var	*temp;
// 	t_var	*new_var;

// 	temp = shell->envvars;
// 	while (temp != NULL)
// 	{
// 		if (strcmp(temp->name, argument->arg) == 0)
// 			return (0);
// 		temp = temp->next;
// 	}
// 	new_var = malloc(sizeof(t_var));
// 	if (new_var == NULL)
// 		return (1);
// 	new_var->content = strdup(argument->arg);
// 	new_var->name = strdup(argument->arg);
// 	new_var->value = NULL;
// 	new_var->env = false;
// 	new_var->exp = true;
// 	new_var->prev = NULL;
// 	if (shell->envvars != NULL)
// 		shell->envvars->prev = new_var;
// 	new_var->next = shell->envvars;
// 	shell->envvars = new_var;
// 	return (0);
// }

/*static int	find_equal_position(char *arg)
{
	int i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] == '=')
			return i;
		i++;
	}
	return (-1);
}*/

/*static int update_var(t_minishell *shell, char *name, char *value)
{
	t_var *var;

	var = shell->envvars;
	while (var != NULL)
	{
		if (strcmp(var->name, name) == 0)
		{
			free(var->value);
			var->value = value;
			free(name); // Nome não é mais necessário
			return 0; // Sucesso
		}
		var = var->next;
	}
	return -1; // Não encontrou a variável para atualizar
}

static int	create_var(t_minishell *shell, char *name, char *value)
{
	t_var *var;

	var = malloc(sizeof(t_var));
	if (!var)
	{
		free(name);
		free(value);
		return 1; // Erro de alocação
	}
	var->name = name;
	var->value = value;
	var->env = true;
	var->exp = true;
	var->content = create_envvar_content(name, value);
	var->next = shell->envvars; // Adiciona no início da lista
	shell->envvars = var;
	return 0;
}

static int update_or_create_var(t_minishell *shell, char *name, char *value)
{
	if (update_var(shell, name, value) == 0)
		return 0; // Variável atualizada com sucesso
	// Se a variável não foi atualizada, tenta criar uma nova
	return (create_var(shell, name, value));
}

static int	update_or_create_var(t_minishell *shell, char *name, char *value)
{
	t_var *var;

	var = shell->envvars;
	while (var != NULL)
	{
		if (strcmp(var->name, name) == 0)
		{
			free(var->value);
			var->value = value;
			free(name); // Nome não é mais necessário
			return 0; // Sucesso
		}
		var = var->next;
	}
	var = malloc(sizeof(t_var));
	if (!var) {
		free(name);
		free(value);
		return 1; // Erro de alocação
	}
	var->name = name;
	var->value = value;
	var->env = true;
	var->exp = true;
	var->content = create_envvar_content(name, value);
	var->next = shell->envvars; // Adiciona no início da lista
	shell->envvars = var;
	return 0;
}

static int handle_with_equal(t_minishell *shell, t_arg *argument)
{
	int	equal_pos;
	char *name;
	char *value;

	equal_pos = find_equal_position(argument->arg);
	if (equal_pos == -1)
		return 1;
	name = strndup(argument->arg, equal_pos);
	value = strdup(argument->arg + equal_pos + 1);
	return (update_or_create_var(shell, name, value));
}*/
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
	name = strndup(argument->arg, equal_pos);
	value = strdup(argument->arg + equal_pos + 1);
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
	var->content = create_envvar_content(name, value);
	var->next = shell->envvars;
	shell->envvars = var;
	return (0);
}

static int	handle_export_args(t_minishell *shell)
{
	t_arg	*temp;
	int		exit_status;

	exit_status = 0;
	temp = shell->commands->arguments;
	while (temp != NULL)
	{
		if (temp->arg[0] == '_' && temp->arg[1] == '=')
			return (0);
		if (is_valid_arg(temp->arg) == false)
			printf("minishell: export: `%s': not a valid identifier\n", \
			temp->arg);
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
	t_var *temp;

	temp = a->next;
	a->next = b;
	a->prev = b->prev;
	b->prev = a;
	b->next = temp;
	temp->prev = b;
}


// curr --> next --> next->next || curr->next = next->next; next->next->prev = curr; curr->prev = next; next->next = curr;
// next --> curr --> next->next

// void	swap_nodes(t_var *curr, t_var *next)
// {
// 	t_var	*temp;

// 	temp = next->next;
// 	if (curr->prev != NULL)
// 		curr->prev->next = next;
// 	if (temp != NULL)
// 		temp->prev = curr;
// 	next->prev = curr->prev;
// 	curr->prev = next;
// 	curr->next = temp;
// 	next->next = curr;
// }

void	sort_content(t_var *envvar_list)
{
	t_var	*current;
	t_var	*next;

	if (envvar_list == NULL)
		return ;
	current = envvar_list;
	while (current != NULL)
	{
		next = current->next;
		while (next != NULL)
		{
			if (ft_strcmp(current->content, next->content) > 0)
				swap_nodes(current, next);
			next = next->next;
		}
		current = current->next;
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
		}
		return (0);
	}
	else
		return (handle_export_args(shell));
}
