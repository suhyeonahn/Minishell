/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 03:26:08 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 03:26:10 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exec_no_builtin(t_mini *mini, t_cmd *cmd, char *path, char ***env)
{
	int	status;

	if (!find_slash(cmd->argv[0]) && path)
		status = execve(path, cmd->argv, *env);
	else if (find_slash(cmd->argv[0]) == -1)
	{
		if (path != cmd->cmd)
			free(path);
		free_t_mini(mini);
		free_env(*env);
		exit(0);
	}
	else
		status = execve(cmd->argv[0], cmd->argv, *env);
	if (status == -1)
	{
		write(2, "minishell: ", 12);
		write(2, cmd->cmd, ft_strlen(cmd->cmd));
		write(2, ":command not found\n", 19);
		if (path != cmd->cmd)
			free(path);
		free_t_mini(mini);
		free_env(*env);
		exit(127);
	}
}

void	exec_box_child(t_mini *mini, t_cmd *cmd, char *path, char ***env)
{
	int	status;

	status = -1;
	if (g_sig.has_child == 1)
		status = check_builtins(mini, cmd, env);
	if (status == 2 || g_sig.has_child == 0)
		exec_no_builtin(mini, cmd, path, env);
	if (path != cmd->cmd)
		free(path);
	free_t_mini(mini);
	free_env(*env);
	exit(status);
}

void	check_sigint(void)
{
	if (g_sig.sigint == 1)
	{
		g_sig.exit_status = 130;
		return ;
	}
	else if (g_sig.sigquit == 1)
	{
		g_sig.exit_status = 131;
		return ;
	}
}

void	exec_box(t_mini *mini, t_cmd *cmd, char *path, char ***env)
{
	int	status;

	status = -1;
	check_signal_hd();
	g_sig.pid = fork();
	if (g_sig.pid == -1)
		exit_error("pid");
	if (g_sig.pid == 0)
		exec_box_child(mini, cmd, path, env);
	else
	{
		waitpid(g_sig.pid, &status, 0);
		check_signal();
		if (WIFEXITED(status))
			g_sig.exit_status = WEXITSTATUS(status);
		if (!ft_strcmp(cmd->input.filename, cmd->hd_name))
		{
			close(cmd->input.fd);
			unlink(cmd->hd_name);
		}
	}
	check_sigint();
}
