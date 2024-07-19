/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_creation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 20:16:11 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/19 15:10:44 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void check_token(t_token *input)
{
	int i;

	i = -1;
	if (input->content == NULL)
		return ;
	while (input->content[++i])
	{
		if (input->content[i] == N_DQUOTE)
			input->dq = true;
		else if (input->content[i] == N_SQUOTE)
			input->sq = true;
		else if (input->content[i] == N_DOLLAR)
			input->dol = true;
		else if (input->content[i] == EQUAL)
			input->equal = true;
	}
	
}

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
	else if (ft_check_equal(token) && (!token->prev
		|| (token->prev->type >= T_RTRUNC)))
		token->type = T_EQUAL;
	else if (!token->prev || token->prev->type >= T_RTRUNC)
		token->type = T_COMMAND;
	else
		token->type = T_ARG;
}

static void	init_token(t_minishell *shell, char *value)
{
	t_token *new_token;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
	{
		//free everything
		printf("init token\n");
		exit (1);
	}
	new_token->type = -1;
	new_token->content = ft_strdup(value);
	ft_tokenadd_back(&shell->tokens, new_token);
}

void include_token(t_minishell *shell, char *input, t_token *argument)
{
	t_token *new;
	t_token *curr;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
	{
		printf("Error: malloc failed 1\n");
		exit (1);
	}
	new->content = ft_strdup(input);
	new->type = -1;
	new->expanded = true;
	curr = shell->tokens;
	while (curr->next && curr != argument)
		curr = curr->next;
	new->prev = curr;
	new->next = curr->next;
	curr->next = new;
	if (new->next)
		new->next->prev = new;
}

void	token_creation(char **array, t_minishell *shell)
{
	int i;
	t_token *tmp;

	i = -1;
	while (array[++i] != NULL)
		init_token(shell, array[i]);
	tmp = shell->tokens;
	while (tmp)
	{
		check_token(tmp);
		tmp->content = quote_del(tmp->content, shell);
		get_type(tmp);
		tmp = tmp->next;
	}
}
