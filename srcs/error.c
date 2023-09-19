/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:45:42 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 04:45:43 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(char *error)
{
	perror(error);
	exit(EXIT_FAILURE);
}

int	msg_error(t_parse_cmd *p)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token `|`\n", 39);
	g_sig.exit_status = 2;
	g_sig.syntax_error = 1;
	free_t_cmd_list(p->cmds);
	free(p);
	return (2);
}

void	parse_syntax_error(t_mini *mini)
{
	g_sig.exit_status = 2;
	g_sig.syntax_error = 1;
	mini->ret = 2;
}
