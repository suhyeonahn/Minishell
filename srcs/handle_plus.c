/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:07:41 by suahn             #+#    #+#             */
/*   Updated: 2022/05/09 16:07:42 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_new_var_plus(char *src, char ***env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (src[i] && src[i] != '+')
		i++;
	tmp = ft_strjoin(ft_substr(src, 0, i),
			ft_substr(src, i + 1, ft_strlen(src) - (i + 1)));
	(*env) = add_var((*env), tmp);
	free(tmp);
}

void	handle_plus(char **argv, char ***env, t_var *v)
{
	char	*tmp;

	v->ret--;
	while ((*env) && (*env)[v->j])
	{
		if (!ft_strncmp(argv[v->i], (*env)[v->j], v->ret))
		{
			if (argv[v->i][v->ret])
			{
				tmp = ft_strjoin((*env)[v->j],
						ft_substr(argv[v->i], v->ret + 2,
							ft_strlen(argv[v->i]) - (v->ret + 1)));
				free((*env)[v->j]);
				(*env)[v->j] = ft_strcpy(tmp);
				free(tmp);
			}
			break ;
		}
		v->j++;
	}
	if (!(*env)[v->j])
		add_new_var_plus(argv[v->i], env);
}
