/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/20 15:46:27 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

// $ handle here? add a flag on the structure to analyze if the expansion is needed

void	parsing_hub(char *input, t_minishell *shell)
{
	input_manager(&input);
	shell->tokens = token_manager(input);
	analyze_argument(shell->tokens, shell);
}
