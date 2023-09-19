/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:06:56 by suahn             #+#    #+#             */
/*   Updated: 2022/04/02 14:06:58 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd_list	*new_t_cmd_list(void)
{
	t_cmd_list	*list;

	list = malloc(sizeof(t_cmd_list));
	if (!list)
		return (NULL);
	list->start = NULL;
	return (list);
}

void	add_cmd_node_to_list(t_cmd_list *list, t_cmd_node *cmd_node)
{
	t_cmd_node	*n;

	if (list->start == NULL)
		list->start = cmd_node;
	else
	{
		n = list->start;
		while (1)
		{
			if (n->next == NULL)
			{
				n->next = cmd_node;
				break ;
			}
			n = n->next;
		}
	}
}

t_cmd	*new_t_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->content = NULL;
	cmd->cmd = NULL;
	cmd->argv = (char **)malloc(4096 * sizeof(char *));
	if (!cmd->argv)
		return (NULL);
	if (!cmd->argv)
	{
		printf("Cannot allocate memory");
		exit(1);
	}
	cmd->argv[0] = NULL;
	cmd->input.filename = NULL;
	cmd->input.fd = -1;
	cmd->output.filename = NULL;
	cmd->output.fd = -1;
	cmd->output.append = 0;
	cmd->hd_name = NULL;
	return (cmd);
}

t_cmd_node	*new_t_cmd_node(void)
{
	t_cmd_node	*node;

	node = malloc(sizeof(t_cmd_node));
	if (!node)
		return (NULL);
	node->cmd = new_t_cmd();
	node->next = NULL;
	return (node);
}
