/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 17:20:31 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/15 14:43:12 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

// separar aqui as dqs e sqs em argument->next
// para remover as quotes podemos verificar se há duas Nquotes seguidas e fazer um split das strings

static void check_arg(t_arg *input)
{
	int i;

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
		else if (input->arg[i] == N_EQUAL)
			input->equal = true;
	}
	
}

// static void expand_quotes(t_arg *argument)
// {
// 	char *new;
// 	int i;
// 	bool flag;

// 	i = -1;
// 	flag = false;
// 	if (argument->arg == NULL)
// 		return ;
// 	while (argument->arg[++i] != '\0')
// 		if ((argument->arg[i] == N_DQUOTE || argument->arg[i] == N_SQUOTE)
// 			&& ((argument->arg[i + 1] == '\0') || (i != 0)))
// 				break ;
// 			else if (argument->arg[i] == N_DQUOTE || argument->arg[i] == N_SQUOTE)
// 				flag = true;
// 	if (argument->arg[i] == 0)
// 		return ;
// 	if (flag)
// 		i++;
// 	new = ft_strdup(argument->arg + i);
// 	argument->next = (t_arg *)malloc(sizeof(t_arg));
// 	if (!argument->next)
// 		return ;
// 	argument->next->arg = new;
// 	argument->next->next = NULL;
// 	argument->arg[i] = '\0';
// 	if (new[ft_strlen(new)] == 0)
// 		return ;
// 	expand_quotes(argument->next);
// }

// include arg is a function that includes the new argument in the linked list (in the correct position)

static	void include_arg(t_minishell *shell, char *argument)
{
	t_arg *new;
	t_arg *tmp;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
	{
		//free everything
		exit (1);
	}
	new->arg = ft_strdup(argument);
	new->dq = false;
	new->sq = false;
	new->dol = false;
	new->equal = false;
	new->expanded = true;
	while (ft_strncmp(shell->commands->arguments->arg, argument, ft_strlen(argument)) != 0)
		shell->commands->arguments = shell->commands->arguments->next;
	tmp = shell->commands->arguments->next;
	new->prev = shell->commands->arguments;
	new->next = tmp;
	shell->commands->arguments->next = new;
}

// analyze_arguments is a function that analyzes the arguments and expands the quotes and dolar signs

void	analyze_arguments(t_minishell *shell, char *cmd)
{
	while (strcmp(shell->commands->cmd, cmd) != 0)
		shell->commands = shell->commands->next;
	while (shell->commands->arguments != NULL)
	{
		expand_quotes(shell->commands->arguments, shell);
		check_arg(shell->commands->arguments);
		shell->commands->arguments->arg = quote_del(shell->commands->arguments, shell);
		expand_dolar(shell->commands->arguments, shell);
		shell->commands->arguments = shell->commands->arguments->next;
	}
}
