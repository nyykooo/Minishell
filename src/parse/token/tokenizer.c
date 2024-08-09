/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 11:25:37 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void	mark_tokens(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\'' || input[i] == '\"')
			i = ft_skip_quotes(input, &i);
		if (input[i] == ' ')
			input[i] *= -1;
	}
}

static void	clear_commands(t_cmd *command)
{
	t_cmd	*tmp;

	tmp = command;
	while (tmp)
	{
		tmp->cmd = ft_quote_del(tmp->cmd);
		tmp = tmp->next;
	}
}

static void	reset_shell(t_minishell *shell)
{
	while (shell->commands)
	{
		while (shell->commands->arguments)
		{
			if (shell->commands->arguments->prev)
				shell->commands->arguments = shell->commands->arguments->prev;
			else
				break ;
		}
		if (shell->commands->prev)
			shell->commands = shell->commands->prev;
		else
			break ;
	}
}

void	ft_tokenizer(t_minishell *shell)
{
	char	**array;

	ft_expand_dolar(&shell->input, shell);
	ft_expand_tildes(&shell->input, shell);
	ft_expand_hashtag(&shell->input);
	ft_expand_pipes_redir(shell);
	mark_tokens(shell->input);
	array = ft_split(shell->input, N_SPACE);
	if (!array)
	{
		ft_free_shell(shell);
		exit(1);
	}
	ft_token_creation(array, shell);
	ft_free_array(array);
	if (ft_verify_unexpected_token(shell) && ft_verify_fn(shell))
	{
		ft_analyze_tokens(shell->tokens, shell);
		reset_shell(shell);
		clear_commands(shell->commands);
		ft_mark_commands(shell);
	}
}
