/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:16:11 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/17 17:46:26 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void	get_type(t_token *token)
{
	if (ft_strcmp(token->content, "") == 0)
		token->type = T_EMPTY;
	else if (ft_strcmp(token->content, ">") == 0)
		token->type = T_RTRUNC;
	else if (ft_strcmp(token->content, ">>") == 0)
		token->type = T_RAPEND;
	else if (ft_strcmp(token->content, "<") == 0)
		token->type = T_LTRUNC;
	else if (ft_strcmp(token->content, "<<") == 0)
		token->type = T_LAPEND;
	else if (ft_strcmp(token->content, "|") == 0)
		token->type = T_PIPE;
	else if (!token->prev || token->prev->type >= T_RTRUNC)
		token->type = T_COMMAND;
	else
		token->type = T_ARG;
}

static void	init_token(t_minishell *shell, char *value)
{
	t_token *new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
	{
		//free everything
		printf("init token\n");
		exit (1);
	}
	new_token->type = -1;
	new_token->content = ft_strdup(value);
	new_token->prev = NULL;
	new_token->next = NULL;
	ft_tokenadd_back(&shell->tokens, new_token);
}

void	token_creation(char **array, t_minishell *shell)
{
	int i;

	i = -1;
	while (array[++i] != NULL)
		init_token(shell, array[i]);
	while (shell->tokens->next != NULL)
	{
		get_type(shell->tokens);
		shell->tokens = shell->tokens->next;
	}
	get_type(shell->tokens);
	while (shell->tokens->prev != NULL)
		shell->tokens = shell->tokens->prev;
}