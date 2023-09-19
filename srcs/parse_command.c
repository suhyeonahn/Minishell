/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:33:07 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:33:08 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*after_chevron(t_mini *mini, char *str, char **env,
			t_tokenize_state *state)
{
	close_token(str, state, env);
	handle_redirect(mini, env, str, state);
	state->i--;
	if (g_sig.exit_status != 0)
	{
		g_sig.syntax_error = 1;
		free_t_cmd(state->cmd);
		return (NULL);
	}
	return ("SUCCESS");
}

t_cmd	*parse_command(t_mini *mini, char *str, char **env, int cmd_i)
{
	t_tokenize_state	state;
	t_cmd				*cmd;

	init_t_tokenize_state(&state, cmd_i);
	while (str[state.i])
	{
		handle_quotes(str, &state);
		if (char_is_in(str[state.i], "<>"))
		{
			if (after_chevron(mini, str, env, &state) == NULL)
				return (NULL);
		}
		else if (str[state.i] == ' ')
			close_token(str, &state, env);
		else if (!state.in_token)
		{
			state.last = state.i;
			state.in_token = 1;
		}
		if (state.i != (int)ft_strlen(str))
			state.i++;
	}
	close_token(str, &state, env);
	cmd = state.cmd;
	return (cmd);
}
