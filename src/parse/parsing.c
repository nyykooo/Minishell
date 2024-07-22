/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:05:16 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/22 23:08:00 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	parsing_hub(t_minishell *shell)
{
	shell->exit_status = input_manager(shell); // check if input is valid and trim spaces
	if (shell->exit_status == 0)
		tokenizer(shell); // create tokens from input and analyze them to create the command list
}