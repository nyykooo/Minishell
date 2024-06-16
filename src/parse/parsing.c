/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 14:05:16 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/13 14:20:14 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

void	parsing_hub(t_minishell *shell)
{
	input_manager(shell); // check if input is valid and trim spaces
	tokenizer(shell); // create tokens from input and analyze them to create the command list
	// analyze_argument(shell);
}