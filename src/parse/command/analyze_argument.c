/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:20:31 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/13 19:45:22 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static void	ft_check_arg(t_arg *input)
{
	int	i;

	i = -1;
	if (input->arg == NULL)
		return ;
	while (input->arg[++i])
	{
		if (input->arg[i] == N_DQUOTE)
			input->dq = true;
		else if (input->arg[i] == N_SQUOTE)
			input->sq = true;
		else if (input->arg[i] == N_DOLLAR)
			input->dol = true;
		else if (input->arg[i] == EQUAL)
			input->equal = true;
	}
}

void	ft_include_arg(t_minishell *shell, char *input, t_arg *argument)
{
	t_arg	*new;
	t_arg	*curr;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
	{
		printf("Error: malloc failed 1\n");
		exit (1);
	}
	new->arg = ft_strdup(input);
	new->dq = false;
	new->sq = false;
	new->dol = false;
	new->equal = false;
	new->expanded = true;
	curr = shell->commands->arguments;
	while (curr->next && curr != argument)
		curr = curr->next;
	new->prev = curr;
	new->next = curr->next;
	curr->next = new;
	if (new->next)
		new->next->prev = new;
}

void	ft_analyze_arguments(t_minishell *shell, t_cmd *cmd)
{
	t_arg	*tmp;

	(void)shell;
	tmp = cmd->arguments;
	while (tmp != NULL)
	{
		ft_check_arg(tmp);
		tmp = tmp->next;
	}
}
