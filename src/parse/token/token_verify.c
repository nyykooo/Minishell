/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verify.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:00:23 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 20:07:22 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static bool	ft_verify_pipe(t_token *token)
{
	if (token->type == T_PIPE && (!token->prev
			|| (token->next && token->next->type == T_PIPE)))
	{
		ft_print_error(false, 2, 1,
			"minishell: syntax error near unexpected token `|'\n");
		return (false);
	}
	return (true);
}

static bool	ft_verify_newline(t_token *token)
{
	if (!token->next)
	{
		ft_print_error(false, 2, 1,
			"minishell: syntax error near unexpected token `newline'\n");
		return (false);
	}
	return (true);
}

static bool	ft_verify_redirs(t_token *token)
{
	if (token->type != T_PIPE && token->next->type >= T_RTRUNC)
	{
		ft_print_error(false, 2, 3,
			"minishell: syntax error near unexpected token `",
			token->next->content, "'\n");
		return (false);
	}
	return (true);
}

bool	ft_verify_unexpected_token(t_minishell *shell)
{
	t_token	*token;

	token = shell->tokens;
	while (token)
	{
		if (token->type >= T_RTRUNC && token->type <= T_PIPE)
		{
			if (!ft_verify_pipe(token))
				return (false);
			if (!ft_verify_newline(token))
				return (false);
			if (!ft_verify_redirs(token))
				return (false);
		}
		token = token->next;
	}
	return (true);
}

bool	ft_verify_fn(t_minishell *shell)
{
	t_token	*token;

	token = shell->tokens;
	if (!token)
		return (false);
	if (!token->next && ft_strcmp(token->content, ".") == 0)
	{
		ft_print_error(false, 2, 1,
			"minishell: .: filename argument required\n");
		return (false);
	}
	return (true);
}
