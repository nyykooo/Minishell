/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_charlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 11:22:43 by ncampbel          #+#    #+#             */
/*   Updated: 2024/04/14 11:29:44 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_charlen(char c)
{
	int	len;

	if (c & 0x80)
		len = 1;
    else if ((c & 0xC0) == 0x80)
        len = 0;
	else if ((c & 0xE0) == 0xC0)
		len = 2;
	else if ((c & 0xF0) == 0xE0)
		len = 3;
	else if ((c & 0xF8) == 0xF0)
		len = 4;
	else
		return (-1);
	return (len * 8);
}