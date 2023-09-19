/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:34:17 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:34:18 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rm_quotes(t_quote *q, char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * (ft_strlen(str) - q->n_quote) + 1);
	if (!new)
		return (NULL);
	while (str[i])
	{
		if (in_tab(i, q) == 1)
			i++;
		else
		{
			new[j] = str[i];
			j++;
			i++;
		}
	}
	new[j] = '\0';
	return (new);
}

void	rm_quotes_routine(char *s, t_quote *q)
{
	while (s[q->i])
	{
		if (q->quote == '\0' && (s[q->i] == '\'' || s[q->i] == '\"'))
		{
			q->quote = s[q->i];
			update_quote(q);
		}
		else if (q->quote != '\0' && s[q->i] == q->quote)
		{
			q->quote = '\0';
			update_quote(q);
		}
		else
			q->len++;
		q->i++;
	}
}

char	*remove_quotes(char *s)
{
	t_quote	*q;
	char	*new;

	q = new_t_quote();
	if (s == NULL)
	{
		free_t_quote(q);
		return (NULL);
	}
	rm_quotes_routine(s, q);
	new = rm_quotes(q, s);
	if (s)
		free(s);
	free_t_quote(q);
	return (new);
}
