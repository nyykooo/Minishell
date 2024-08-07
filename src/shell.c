/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:58:38 by ncampbel          #+#    #+#             */
/*   Updated: 2024/08/07 16:21:44 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libs/headers.h"

t_minishell	*ft_get_shell(void)
{
	static t_minishell	shell;

	return (&shell);
}
