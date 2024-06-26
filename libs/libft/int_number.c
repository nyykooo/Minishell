/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 16:25:31 by ncampbel          #+#    #+#             */
/*   Updated: 2024/06/12 16:54:48 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	int_number(const char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (nbr[i] == '-' || nbr[i] == '+')
			i++;
		while (nbr[i] == '0')
			i++;
		if (ft_strlen(nbr + i) >= 11)
			return (false);
		else
			return (true);
	}
	return (true);
}
