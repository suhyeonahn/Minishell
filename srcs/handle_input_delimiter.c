/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_delimiter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:32:57 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:17:58 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_input_dl(t_mini *mini, char **env,
			t_tokenize_state *state, t_input_delimiter *id)
{
	free(id->delimiter);
	if (ft_strcmp("", id->in))
		free(id->in);
	close(state->cmd->input.fd);
	unlink(state->cmd->hd_name);
	free(mini->substr);
	free_t_cmd_list(mini->p->cmds);
	free(mini->p);
	free_t_cmd(state->cmd);
	free(mini->node);
	free_t_mini(mini);
	free_env(env);
	exit(0);
}

void	free_input_dl2(t_mini *mini, char **env,
		t_tokenize_state *state, t_input_delimiter *id)
{
	write(state->cmd->input.fd, id->in, ft_strlen(id->in));
	close(state->cmd->input.fd);
	free(id->delimiter);
	free(id->in);
	free(mini->substr);
	free_t_cmd_list(mini->p->cmds);
	free(mini->p);
	free_t_cmd(state->cmd);
	free(mini->node);
	free_t_mini(mini);
	free_env(env);
	exit(0);
}

void	child_input_delimiter(t_mini *mini, char **env,
		t_tokenize_state *state, t_input_delimiter *id)
{
	check_signal_hd();
	while (1)
	{
		id->buf = readline("> ");
		if (g_sig.sigint_hd)
			free_input_dl(mini, env, state, id);
		else if (!id->buf)
		{
			write(2, "minishell: here-doc exited with ctrl-D\n", 39);
			free_input_dl(mini, env, state, id);
		}
		if (!ft_strcmp(id->buf, id->delimiter))
			free_input_dl2(mini, env, state, id);
		id->tmp = ft_strcpy(id->in);
		if (ft_strcmp(id->in, ""))
			free(id->in);
		id->in = ft_strjoin2(id->tmp, id->buf);
		free(id->tmp);
		free(id->buf);
	}
}

void	parent_input_delimiter(t_tokenize_state *state, t_input_delimiter *id)
{
	waitpid(g_sig.pid, &id->status, 0);
	close(state->cmd->input.fd);
	free(id->delimiter);
	state->cmd->input.fd = open(id->name, O_RDONLY);
	if (WIFEXITED(id->status))
		g_sig.exit_status = WEXITSTATUS(id->status);
	if (g_sig.exit_status == 130)
		g_sig.syntax_error = 1;
}

void	handle_input_delimiter(t_mini *mini, char **env,
		t_tokenize_state *state, char *delimiter)
{
	t_input_delimiter	id;

	id.delimiter = delimiter;
	if (g_sig.syntax_error == 1)
		return ;
	id.name = state->cmd->hd_name;
	if (state->cmd->input.filename)
	{
		free(state->cmd->input.filename);
		state->cmd->input.filename = NULL;
		close(state->cmd->input.fd);
		state->cmd->input.fd = -1;
	}
	state->cmd->input.filename = ft_strcpy(id.name);
	state->cmd->input.fd = open(id.name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	id.in = "";
	g_sig.pid = fork();
	if (g_sig.pid == 0)
		child_input_delimiter(mini, env, state, &id);
	else
		parent_input_delimiter(state, &id);
}
