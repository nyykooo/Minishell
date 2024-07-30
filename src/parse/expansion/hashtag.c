/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtag.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:50:53 by ncampbel          #+#    #+#             */
/*   Updated: 2024/07/30 19:13:09 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../libs/headers.h"

void	expand_hashtag(char **input)
{
	
	int		i;

	i = -1;
	while ((*input)[++i])
	{
		if ((*input)[i] == '#' && ft_is_inside_quotes((*input), i) == 0 && (*input)[i - 1] == ' ')
			(*input)[i] = 0;
	}
}
