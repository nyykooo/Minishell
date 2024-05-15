/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 09:43:57 by ncampbel          #+#    #+#             */
/*   Updated: 2023/10/23 17:29:53 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*memory;
	size_t	len;

	len = (nmemb * size);
	if (nmemb == 0 || size == 0)
		len = 1;
	memory = malloc(len);
	if (memory == NULL)
		return (NULL);
	ft_bzero(memory, len);
	return (memory);
}
