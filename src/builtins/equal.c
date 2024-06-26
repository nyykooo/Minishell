/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:24:08 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/26 13:42:49 by ncampbel         ###   ########.fr       */
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

void	handle_equal(t_minishell *shell, t_cmd *command)
{
	t_var	*new_var;
	
	new_var = malloc(sizeof(t_var));
	if (new_var == NULL)
	{
		write(2, "Error: malloc failed\n", 21);
		return ;
	}
	new_var->content = ft_strdup(command->cmd);
	new_var->name = ft_substr(command->cmd, 0, ft_strchr(command->cmd, '=') - command->cmd);
	new_var->value = ft_strdup(ft_strchr(command->cmd, '=') + 1);
	new_var->env = false;
	ft_varadd_back(&shell->envvars, new_var);
}
