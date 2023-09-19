/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:33:41 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:33:42 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_output_file(t_tokenize_state *state,
		char *identifier, int append)
{
	int	fd;

	if (append)
		fd = open(identifier, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(identifier, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		g_sig.exit_status = 127;
		perror(identifier);
		return ;
	}
	if (state->cmd->output.filename)
		free(state->cmd->output.filename);
	state->cmd->output.filename = identifier;
	if (state->cmd->output.fd)
		close(state->cmd->output.fd);
	state->cmd->output.fd = fd;
	state->cmd->output.append = append;
}
