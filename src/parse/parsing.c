/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:05:16 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/15 12:20:31 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	ft_parsing_hub(t_minishell *shell)
{
	bool	continue_loop;

	continue_loop = ft_input_manager(shell);
	if (continue_loop)
		ft_tokenizer(shell);
}
