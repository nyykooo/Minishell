/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brunhenr <brunhenr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 18:52:26 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 13:19:25 by brunhenr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strreplace(char *src, int i, char *insert, char *name)
{
	char	*str_frag;
	char	*tmp;
	char	*new;

	str_frag = ft_substr(src, 0, i);
	tmp = ft_strjoin(str_frag, insert);
	new = ft_strjoin(tmp, src + i + ft_strlen(name) + 1);
	free(str_frag);
	free(tmp);
	free(src);
	return (new);
}
