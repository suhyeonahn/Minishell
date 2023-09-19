/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:38:24 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:18:18 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	inside_sq(char *str, int dollar)
{
	int		i;
	char	quote;

	quote = '\0';
	i = 0;
	while (str[i])
	{
		if (quote == '\'' && i == dollar)
			return (1);
		else if (quote == '\0' && (str[i] == '\'' || str[i] == '\"'))
			quote = str[i];
		else if (quote != '\0' && str[i] == quote)
			quote = '\0';
		i++;
	}
	return (0);
}

void	is_var(t_dollar *d, char *var)
{
	char	*tmp;

	if (d->new == NULL)
		d->new = ft_strcpy(var);
	else if (var)
	{
		tmp = ft_strjoin(d->new, var);
		free(d->new);
		d->new = ft_strcpy(tmp);
		free(tmp);
		free(var);
		var = NULL;
	}
	if (var)
		free(var);
}

void	no_question_mark(char **env, char *str, t_dollar *d)
{
	char	*var;
	char	*new_var;

	var = get_var_value(env, ft_substr(str, d->i,
				check_dollar_var_name(&str[d->i])));
	if (d->i < 1 || (d->i >= 2 && str[d->i - 2] != '\"'))
	{
		new_var = var_without_white_space(var);
		free(var);
		var = new_var;
	}
	is_var(d, var);
	d->i += check_dollar_var_name(&str[d->i]);
	d->start = d->i;
}

void	found_question_mark(t_dollar *d)
{
	char	*tmp;
	char	*itoa;

	itoa = ft_itoa(g_sig.exit_status);
	if (d->new == NULL)
		d->new = ft_strcpy(itoa);
	else
	{
		tmp = ft_strjoin(d->new, ft_strcpy(itoa));
		free(d->new);
		d->new = ft_strcpy(tmp);
		free(tmp);
	}
	d->i++;
	d->start = d->i;
	free(itoa);
}

char	*handle_dollar(char *str, char **env)
{
	t_dollar	d;

	d.i = 0;
	d.start = 0;
	d.new = NULL;
	while (d.i <= (int)ft_strlen(str) && str[d.i])
	{
		if (str[d.i] == '$')
		{
			d.i++;
			if (inside_sq(str, d.i - 1))
				;
			else if (!str[d.i] || str[d.i] == ' ' || str[d.i] == ':'
				|| str[d.i] == '\"' || str[d.i] == '=')
				d.i++;
			else if (str[d.i] == '?')
				found_question_mark(&d);
			else
				no_question_mark(env, str, &d);
		}
		while ((d.i <= (int)ft_strlen(str)) && str[d.i] && str[d.i] != '$')
			d.i++;
		write_new_line(str, &d);
	}
	return (d.new);
}
