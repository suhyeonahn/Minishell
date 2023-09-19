/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 01:16:07 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 01:16:09 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_argv(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->argv[i] != NULL)
	{
		free(cmd->argv[i]);
		i++;
	}
	free(cmd->argv);
}

void	free_t_cmd(t_cmd *cmd)
{
	if (cmd)
	{
		if (cmd->argv)
			free_argv(cmd);
		if (cmd->content)
			free(cmd->content);
		if (cmd->input.fd > 2)
			close(cmd->input.fd);
		if (cmd->output.fd > 2)
			close(cmd->output.fd);
		if (cmd->input.filename)
			free(cmd->input.filename);
		if (cmd->output.filename)
			free(cmd->output.filename);
		if (cmd->hd_name)
			free(cmd->hd_name);
		free(cmd);
	}
}

void	free_t_cmd_node(t_cmd_node *cmd_node)
{
	if (cmd_node)
	{
		if (cmd_node->next)
			free_t_cmd_node(cmd_node->next);
		if (cmd_node->cmd)
			free_t_cmd(cmd_node->cmd);
		free(cmd_node);
	}
}

void	free_t_cmd_list(t_cmd_list *list)
{
	if (list)
	{
		if (list->start)
			free_t_cmd_node(list->start);
		free(list);
		list = NULL;
	}
}
