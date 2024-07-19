/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guest <guest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:49:42 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/19 15:52:30 by guest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

static	void	init_arg(t_cmd *command, char *argument)
{
	t_arg *arg;

	arg = ft_calloc(1, sizeof(t_arg));
	ft_argadd_back(&command->arguments, arg);
	arg->arg = ft_strdup(argument);
}

static	void	init_cmd(t_minishell *shell, t_token *tokens)
{
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	ft_cmdadd_back(&shell->commands, cmd);
	cmd->cmd = ft_strdup(tokens->content);
	cmd->type = tokens->type;
	cmd->shell = shell;
	cmd->here_doc_fd = -1;
	tokens = tokens->next;
	while (tokens && (tokens->type == T_ARG || tokens->type == T_EMPTY))
	{
		init_arg(cmd, tokens->content);
		tokens = tokens->next;
	}
}

void	create_command(t_token *tokens, t_minishell *shell)
{
	t_token *tmp;

	tmp = tokens;
	init_cmd(shell, tmp);
	if (!shell->commands)
	{
		//free everything
		printf("Error: malloc failed create commands\n");
		exit (1);
	}
	
}
