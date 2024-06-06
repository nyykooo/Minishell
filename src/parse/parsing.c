/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 13:11:35 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/06 17:00:02 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"

// $ handle here? add a flag on the structure to analyze if the expansion is needed

t_token **parsing_hub(char *input)
{
	input_manager(&input);
	return (token_manager(input));
}
