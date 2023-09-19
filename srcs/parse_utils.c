/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 19:32:42 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 19:32:43 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	char_is_in(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (c);
		i++;
	}
	return (0);
}

char	*hd_name(int cmd_i)
{
	char	*hd_name;
	char	*nb;
	char	*tmp;

	nb = ft_itoa(cmd_i);
	hd_name = ft_strjoin("here_doc", nb);
	tmp = ft_strcpy(hd_name);
	free(hd_name);
	hd_name = ft_strjoin("/tmp/", tmp);
	free(tmp);
	free(nb);
	return (hd_name);
}

int	in_tab(int i, t_quote *q)
{
	int	atoi;
	int	j;

	j = 0;
	atoi = -1;
	while (q->quotes_pos[j])
	{
		atoi = ft_atoi(q->quotes_pos[j]);
		if (atoi == i)
			return (1);
		j++;
	}
	return (0);
}

void	init_t_tokenize_state(t_tokenize_state *state, int cmd_i)
{
	state->i = 0;
	state->last = 0;
	state->in_token = 0;
	state->cmd = new_t_cmd();
	state->cmd->hd_name = hd_name(cmd_i);
}
