/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:33:13 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:33:15 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*identifier_err_msg(void)
{
	write(2, "minishell: syntax error near ", 29);
	write(2, "unexpected token `newline or |`\n", 32);
	return (NULL);
}

char	*identifier_err_msg2(char *str, t_tokenize_state *state)
{
	write(2, "minishell: syntax error near unexpected token `", 47);
	write(2, &str[state->i], 1);
	write(2, "`\n", 2);
	return (NULL);
}

void	init_t_identifier(t_identifier *id, t_tokenize_state *state, int ld)
{
	id->start = state->i;
	id->done_leading_spaces = ld;
}

char	*id_routine(char *str, t_tokenize_state *state, t_identifier *id)
{
	while (state->i <= (int)ft_strlen(str) && str[state->i])
	{
		if (char_is_in(str[state->i], "|<>"))
		{
			if (!char_is_in(str[state->i - 1], "|<> "))
				break ;
			return (identifier_err_msg2(str, state));
		}
		else if (str[state->i] == ' ' && id->done_leading_spaces)
			break ;
		else if (str[state->i] != ' ')
		{
			if (!id->done_leading_spaces)
				init_t_identifier(id, state, 1);
			handle_quotes(str, state);
			if (str[state->i] == ' ')
				break ;
		}
		state->i++;
	}
	return ("SUCCESS");
}

char	*parse_identifier(char *str, t_tokenize_state *state)
{
	t_identifier	id;

	init_t_identifier(&id, state, 0);
	if (!id_routine(str, state, &id))
		return (NULL);
	if ((int)ft_strlen(str) == state->i
		&& str[state->i] == 0 && !id.done_leading_spaces)
		return (identifier_err_msg());
	state->last = state->i;
	id.substr = ft_substr(str, id.start, (state->i - id.start));
	id.start = ft_strlen(id.substr);
	id.substr = remove_quotes(id.substr);
	if ((int)ft_strlen(id.substr) < id.start)
		state->last++;
	return (id.substr);
}
