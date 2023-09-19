/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:33:29 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:22:44 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	in_a_token(t_tokenize_state *state, char *token, int *last_argv)
{
	if (!token && !state->cmd->cmd)
		state->cmd->cmd = "";
	else if (!state->cmd->cmd)
		state->cmd->cmd = token;
	while (state->cmd->argv[*last_argv])
		(*last_argv)++;
	if (!token)
		state->cmd->argv[*last_argv] = "";
	else
		state->cmd->argv[*last_argv] = token;
	state->cmd->argv[*last_argv + 1] = NULL;
}

void	close_token(char *str, t_tokenize_state *state, char **env)
{
	char	*token;
	char	*tmp;
	int		last_argv;

	last_argv = 0;
	if (state->in_token)
	{
		token = ft_substr(str, state->last, (state->i - state->last));
		if (token && ft_strlen(token) > 0)
		{
			tmp = handle_dollar(token, env);
			free(token);
			token = remove_quotes(tmp);
			if (ft_strlen(token) || str[state->last] == '\"'
				|| str[state->last] == '\'')
				in_a_token(state, token, &last_argv);
			state->last = state->i;
			state->in_token = 0;
		}
		else
			free(token);
	}
}
