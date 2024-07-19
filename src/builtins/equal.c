/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/19 15:09:16 by guest            ###   ########.fr       */
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
		{
			token->content[i] = '=';
			return (true);
		}
	}
	return (false);
}

void	handle_equal(t_minishell *shell, t_cmd *command)
{
	t_var	*new_var;
	int		equal;
	
	new_var = ft_calloc(1, sizeof(t_var));
	equal = 0;
	if (new_var == NULL)
	{
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	while (command->cmd[equal] != '=')
		equal++;
	new_var->content = ft_strdup(command->cmd);
	new_var->name = ft_substr(command->cmd, 0, equal);
	new_var->value = ft_substr(command->cmd, equal + 1, ft_strlen(command->cmd) - equal - 1);
	ft_varadd_back(&shell->envvars, new_var);
}
