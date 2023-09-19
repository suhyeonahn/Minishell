/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:38:47 by suahn             #+#    #+#             */
/*   Updated: 2022/03/10 10:59:54 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute(t_mini *mini, t_cmd *cmd, char ***env)
{
	int		status;
	char	*path;

	status = -1;
	if (g_sig.has_child == 0)
		status = check_builtins(mini, cmd, env);
	if (status == 2 || g_sig.has_child == 1)
	{
		path = cmd->cmd;
		if (path)
			path = find_path(cmd->cmd, *env);
		if (cmd->input.fd != -2)
			exec_box(mini, cmd, path, env);
		if (path != cmd->cmd)
			free(path);
	}
	return (g_sig.exit_status);
}

void	redir_and_exec(t_mini *mini, t_cmd_node *cmd, int fd_zero, char ***env)
{
	if (cmd->next)
	{
		if (pipe(mini->pipe_fd) == -1)
			exit_error("pipe");
		g_sig.has_child = 1;
		g_sig.pid = fork();
		if (g_sig.pid == -1)
			exit_error("pid");
		else if (g_sig.pid == 0)
			child_redir(mini, cmd, fd_zero, env);
		else
			parent_redir(mini, cmd, fd_zero, env);
	}
	else
	{
		set_redirs(fd_zero, -1, cmd->cmd);
		execute(mini, cmd->cmd, env);
		if (fd_zero != -1)
			close(fd_zero);
	}
}

void	exec_commands(t_mini *mini, char ***env)
{
	t_cmd_node	*cmd_node;
	int			status;

	mini->parent = 1;
	g_sig.has_child = 0;
	mini->stdout_cpy = dup(STDOUT_FILENO);
	mini->stdin_cpy = dup(STDIN_FILENO);
	cmd_node = mini->cmds->start;
	redir_and_exec(mini, cmd_node, -1, env);
	dup2(mini->stdin_cpy, STDIN_FILENO);
	dup2(mini->stdout_cpy, STDOUT_FILENO);
	close(mini->stdout_cpy);
	close(mini->stdin_cpy);
	waitpid(-1, &status, 0);
	if (mini->parent == 0)
	{
		free_t_mini(mini);
		free_env(*env);
		exit(g_sig.exit_status);
	}
	if (g_sig.has_child == 1 && WIFEXITED(status))
		g_sig.exit_status = WEXITSTATUS(status);
	g_sig.pid = 1;
}
