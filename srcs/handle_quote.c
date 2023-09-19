/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:34:00 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:34:02 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_t_quote(t_quote *q)
{
	int	i;

	i = 0;
	while (q->quotes_pos[i])
	{
		free(q->quotes_pos[i]);
		i++;
	}
	free(q->quotes_pos);
	free(q);
}

t_quote	*new_t_quote(void)
{
	t_quote	*q;

	q = malloc(sizeof(t_quote));
	q->i = 0;
	q->len = 0;
	q->n_quote = 0;
	q->quotes_pos = malloc(sizeof(char *));
	q->quotes_pos[0] = NULL;
	q->quote = '\0';
	return (q);
}

void	update_quote(t_quote *q)
{
	char	**old;
	char	**new;
	int		i;

	i = 0;
	old = q->quotes_pos;
	q->n_quote++;
	new = malloc(sizeof(char *) * (q->n_quote + 1));
	while (old[i])
	{
		new[i] = ft_strcpy(old[i]);
		free(old[i]);
		i++;
	}
	new[i] = ft_itoa(q->i);
	new[i + 1] = NULL;
	free(old);
	q->quotes_pos = new;
}

void	handle_quotes(char *str, t_tokenize_state *state)
{
	char	open_quote;

	if (str[state->i] == '\'' || str[state->i] == '\"')
	{
		if (!state->in_token)
		{
			state->last = state->i;
			state->in_token = 1;
		}
		open_quote = str[state->i];
		state->i++;
		while (str[state->i])
		{
			if (str[state->i] == open_quote)
			{
				state->i++;
				return (handle_quotes(str, state));
			}
			state->i++;
		}
	}
}
