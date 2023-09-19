/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 01:36:43 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 01:36:44 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_mini(t_mini *mini)
{
	if (mini->cmds)
		free_t_cmd_list(mini->cmds);
	free(mini->line);
	if (mini->stdout_cpy != -1)
		close(mini->stdout_cpy);
	if (mini->stdin_cpy != -1)
		close(mini->stdin_cpy);
	if (mini->pipe_fd[0] != -1)
		close(mini->pipe_fd[0]);
	if (mini->pipe_fd[1] != -1)
		close(mini->pipe_fd[1]);
	free(mini);
}

t_mini	*new_t_mini(void)
{
	t_mini	*mini;

	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	mini->p = NULL;
	mini->ret = 0;
	mini->cmd_i = 0;
	mini->stdin_cpy = -1;
	mini->stdout_cpy = -1;
	mini->line = NULL;
	mini->cmds = NULL;
	mini->pipe_fd[0] = -1;
	mini->pipe_fd[1] = -1;
	mini->substr = NULL;
	mini->node = NULL;
	return (mini);
}
