/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/22 22:57:47 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

// parsing do igual vai precisar atuar um pouco diferente do antigo

// bool	check_equal(t_token *token)
// {
// 	int		i;

// 	i = -1;
// 	if (token->content == NULL)
// 		return (false);
// 	while (token->content[++i])
// 	{
// 		if (token->content[i] == N_EQUAL)
// 			return (true);
// 	}
// 	return (false);

// }

bool ft_check_equal(t_token *token)
{
	int i;

	i = -1;
	while (token->content[++i])
	{
		if (token->content[i] == EQUAL)
			return (true);
	}
	return (false);
}

void	handle_equal(t_minishell *shell, t_cmd *command)
{
	t_var	*var;
	char 	*name;
	int		equal;
	
	equal = 0;
	while (command->cmd[equal] != '=')
		equal++;
	name = ft_substr(command->cmd, 0, equal);
	var = find_envvar(shell->envvars, name);
	if (var)
	{
		free(var->value);
		var->value = ft_substr(command->cmd, equal + 1, ft_strlen(command->cmd) - equal - 1);
		free(name);
		return ;
	}
	var = ft_calloc(1, sizeof(t_var));
	if (var == NULL)
	{
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	var->content = ft_strdup(command->cmd);
	var->value = ft_substr(command->cmd, equal + 1, ft_strlen(command->cmd) - equal - 1);
	ft_varadd_back(&shell->envvars, var);
}
