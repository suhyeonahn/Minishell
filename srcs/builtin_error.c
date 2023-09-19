/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 03:26:21 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 03:26:22 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtin_error_msg(char *type, char *argv)
{
	write(2, type, ft_strlen(type));
	write(2, ": `", 3);
	write(2, argv, ft_strlen(argv));
	write(2, "`: not a valid identifier\n", 26);
	g_sig.exit_status = 1;
	return (g_sig.exit_status);
}
