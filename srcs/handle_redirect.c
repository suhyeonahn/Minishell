/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:39:07 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:39:08 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	identifier_absent_error(void)
{
	g_sig.exit_status = 2;
	return ;
}

void	handle_input(t_mini *mini, char **env,
		char *str, t_tokenize_state *state)
{
	char	*identifier;

	identifier = NULL;
	if (!ft_strcmp(state->cmd->input.filename, state->cmd->hd_name))
	{
		close(state->cmd->input.fd);
		unlink(state->cmd->hd_name);
	}
	if (str[state->i + 1] == '<')
	{
		state->i += 2;
		identifier = parse_identifier(str, state);
		if (!identifier)
			return (identifier_absent_error());
		handle_input_delimiter(mini, env, state, identifier);
	}
	else
	{
		state->i += 1;
		identifier = parse_identifier(str, state);
		if (!identifier)
			return (identifier_absent_error());
		handle_input_file(state, identifier);
	}
}

void	handle_output(char *str, t_tokenize_state *state)
{
	char	*identifier;

	identifier = NULL;
	if (str[state->i + 1] == '>')
	{
		state->i += 2;
		identifier = parse_identifier(str, state);
		if (!identifier)
		{
			g_sig.exit_status = 2;
			return ;
		}
		handle_output_file(state, identifier, 1);
	}
	else
	{
		state->i += 1;
		identifier = parse_identifier(str, state);
		if (!identifier)
		{
			g_sig.exit_status = 2;
			return ;
		}
		handle_output_file(state, identifier, 0);
	}
}

void	handle_redirect(t_mini *mini, char **env,
		char *str, t_tokenize_state *state)
{
	if (str[state->i] == '<')
		handle_input(mini, env, str, state);
	else if (str[state->i] == '>')
		handle_output(str, state);
}
