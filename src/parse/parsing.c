/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:05:16 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/09 11:25:52 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_parsing_hub(t_minishell *shell)
{
	shell->exit_status = ft_input_manager(shell);
	if (shell->exit_status == 0)
		ft_tokenizer(shell);
}
