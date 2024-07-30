/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/30 18:31:29 by ncampbel         ###   ########.fr       */
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

void	ft_handle_equal(t_minishell *shell, t_cmd *command)
{
	t_var	*var;
	char 	*name;
	char	*value;
	int		equal;
	
	equal = 0;
	while (command->cmd[equal] != '=')
		equal++;
	name = ft_substr(command->cmd, 0, equal);
	var = ft_find_envvar(shell->envvars, name);
	if (var)
	{
		free(var->value);
		var->value = ft_substr(command->cmd, equal + 1, ft_strlen(command->cmd) - equal - 1);
		free(name);
		return ;
	}
	value = ft_substr(command->cmd, equal + 1, ft_strlen(command->cmd) - equal - 1);
	ft_set_envvar(&shell->envvars, name, value, 0);
	free(name);
	free(value);
}
