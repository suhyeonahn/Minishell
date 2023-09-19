/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:23:53 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 04:23:55 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_redirs(int pipe_read, int pipe_write, t_cmd *cmd)
{
	if (cmd->input.fd > 0)
		dup2(cmd->input.fd, STDIN_FILENO);
	else if (pipe_read != -1)
		dup2(pipe_read, STDIN_FILENO);
	if (cmd->output.fd > 0)
		dup2(cmd->output.fd, STDOUT_FILENO);
	else if (pipe_write != -1)
		dup2(pipe_write, STDOUT_FILENO);
}

void	parent_redir(t_mini *mini, t_cmd_node *cmd, int fd_zero, char ***env)
{	
	close(mini->pipe_fd[0]);
	set_redirs(fd_zero, mini->pipe_fd[1], cmd->cmd);
	execute(mini, cmd->cmd, env);
	if (fd_zero != -1)
		close(fd_zero);
	close(mini->pipe_fd[1]);
}

void	child_redir(t_mini *mini, t_cmd_node *cmd, int fd_zero, char ***env)
{
	mini->parent = 0;
	close(mini->pipe_fd[1]);
	if (fd_zero != -1)
		close(fd_zero);
	redir_and_exec(mini, cmd->next, mini->pipe_fd[0], env);
}
