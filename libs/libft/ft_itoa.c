/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 18:25:43 by ncampbel          #+#    #+#             */
/*   Updated: 2023/10/23 17:33:23 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countsize(int x)
{
	int	i;

	i = 0;
	if (x == 0)
		return (1);
	if (x < 0)
		i++;
	while (x)
	{
		x /= 10;
		i++; 
	}
	return (i);
}

char	*ft_itoa(int c)
{
	char			*new;
	unsigned int	size;
	unsigned int	number;

	size = ft_countsize(c);
	new = (char *)malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	if (c < 0)
	{
		new[0] = '-';
		number = -c;
	}
	else
		number = c;
	if (number == 0)
		new[0] = '0';
	new[size] = '\0';
	while (number)
	{
		new[size - 1] = (number % 10) + 48;
		number /= 10;
		size--;
	}
	return (new);
}
