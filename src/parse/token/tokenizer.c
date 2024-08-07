/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:15:24 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 20:14:20 by ncampbel         ###   ########.fr       */
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
			i = skip_quotes(input, &i);
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
		tmp->cmd = quote_del(tmp->cmd);
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

void	tokenizer(t_minishell *shell)
{
	char	**array;

	expand_dolar(&shell->input, shell);
	expand_tildes(&shell->input, shell);
	expand_hashtag(&shell->input);
	expand_pipes_redir(shell);
	mark_tokens(shell->input);
	array = ft_split(shell->input, N_SPACE);
	if (!array)
	{
		free_shell(shell);
		exit(1);
	}
	token_creation(array, shell);
	free_array(array);
	if (ft_verify_unexpected_token(shell) && ft_verify_fn(shell))
	{
		analyze_tokens(shell->tokens, shell);
		reset_shell(shell);
		clear_commands(shell->commands);
		ft_mark_commands(shell);
	}
}
