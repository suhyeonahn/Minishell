/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:28:23 by suahn             #+#    #+#             */
/*   Updated: 2022/04/02 14:28:24 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_node(t_node *node)
{
	if (node->next)
		free_node(node->next);
	free(node->s);
	free(node);
}

void	free_list(t_list *list)
{
	if (list->start)
		free_node(list->start);
	free(list);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_strarr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int	free_p(t_parse_cmd *p)
{
	free_t_cmd_list(p->cmds);
	free(p);
	return (2);
}
