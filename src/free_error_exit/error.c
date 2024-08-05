/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncampbel <ncampbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:39:12 by brunhenr          #+#    #+#             */
/*   Updated: 2024/08/05 17:13:12 by ncampbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/headers.h"


void	ft_print_error(t_minishell *shell, bool must_free, int exit_status, int nbr, ...)
{
	va_list	arg;
	int		i;
	char	*error_msg;

	error_msg = ft_strdup("");
	i = -1;
	va_start(arg, nbr);
	while (++i < nbr)
		error_msg = ft_strjoin_free(error_msg, va_arg(arg, char *));
	va_end(arg);
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	if (must_free == true)
	{
		free_shell(shell);
		exit(exit_status);
	}
	shell->exit_status = exit_status;
}

char	*error_msg_construct(int nbr, ...)
{
	va_list	arg;
	int		i;
	char	*error_msg;

	error_msg = ft_strdup("");
	i = -1;
	va_start(arg, nbr);
	while (++i < nbr)
		error_msg = ft_strjoin_free(error_msg, va_arg(arg, char *));
	va_end(arg);
	return (error_msg);
}

int	put_error_msg(char *error_msg, int exit_status)
{
	if (error_msg)
		ft_putstr_fd(error_msg, STDERR_FILENO);
	free(error_msg);
	return (exit_status);
}
