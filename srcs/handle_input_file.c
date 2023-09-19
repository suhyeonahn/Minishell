/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:33:51 by suahn             #+#    #+#             */
/*   Updated: 2022/05/11 14:20:38 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_fd(int fd, t_tokenize_state *state, char *identifier)
{
	if (fd == -1)
	{
		state->cmd->input.fd = -2;
		perror(identifier);
	}
	if (fd == state->cmd->input.fd)
		close(fd);
	if (state->cmd->input.filename)
		free(state->cmd->input.filename);
}

void	handle_input_file(t_tokenize_state *state, char *identifier)
{
	int	fd;

	fd = open(identifier, O_RDONLY);
	check_fd(fd, state, identifier);
	if (access(identifier, F_OK) == 0)
		state->cmd->input.filename = identifier;
	else
		state->cmd->input.filename = NULL;
	if (state->cmd->input.fd >= 0)
	{
		close(state->cmd->input.fd);
		state->cmd->input.fd = -1;
	}
	if (access(identifier, F_OK) == 0)
	{
		fd = open(identifier, O_RDONLY);
		state->cmd->input.fd = fd;
	}
	if (state->cmd->input.filename == NULL)
		free(identifier);
}
