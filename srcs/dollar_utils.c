/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:14:06 by suahn             #+#    #+#             */
/*   Updated: 2022/03/28 16:14:08 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*copy_var(char *src, char *new)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] == ' ')
		{
			new[j] = src[i];
			j++;
			i++;
			while (src[i] == ' ')
				i++;
			if (!src[i])
				break ;
		}
		new[j] = src[i];
		i++;
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*var_without_white_space(char *src)
{
	char	*new;
	int		i;
	int		j;

	if (!src)
		return (NULL);
	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i++] == ' ')
		{
			j++;
			while (src[i] == ' ')
				i++;
			if (!src[i])
				break ;
		}
		i++;
		j++;
	}
	new = malloc(j + 1);
	if (!new)
		return (NULL);
	return (copy_var(src, new));
}

void	write_new_line(char *str, t_dollar *d)
{
	char	*tmp;
	char	*substr;

	if (d->start != d->i)
	{
		if (d->new == NULL)
			d->new = ft_substr(str, d->start, d->i - d->start);
		else
		{
			substr = ft_substr(str, d->start, d->i - d->start);
			tmp = ft_strjoin(d->new, substr);
			free(substr);
			free(d->new);
			d->new = ft_strcpy(tmp);
			free(tmp);
		}
		d->start = d->i;
	}
}
