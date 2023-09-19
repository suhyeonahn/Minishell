/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:41:53 by suahn             #+#    #+#             */
/*   Updated: 2022/03/28 14:41:55 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_export_arg(char **argv, char ***env, t_var *v)
{
	while ((*env) && (*env)[v->j])
	{
		if (!ft_strncmp(argv[v->i], (*env)[v->j], v->ret))
		{
			if (argv[v->i][v->ret])
			{
				free((*env)[v->j]);
				(*env)[v->j] = ft_strcpy(argv[v->i]);
			}
			break ;
		}
		v->j++;
	}
}

int	export_arg(char **argv, char ***env)
{
	t_var	v;
	int		var_name;

	v.i = 1;
	v.j = 0;
	while (argv && argv[v.i])
	{
		v.ret = has_var(argv[v.i]);
		var_name = check_var_name(argv[v.i]);
		if (var_name == 1)
			return (builtin_error_msg("export", argv[v.i]));
		else if (var_name == 2)
			handle_plus(argv, env, &v);
		else
		{
			check_export_arg(argv, env, &v);
			if (!(*env)[v.j])
				(*env) = add_var((*env), argv[v.i]);
		}
		v.i++;
	}
	return (0);
}

int	export_no_arg(char ***env)
{
	int	var_name;
	int	j;

	j = 0;
	while ((*env) && (*env)[j])
	{
		write(1, "declare -x ", 11);
		var_name = has_equal((*env)[j]);
		if (var_name)
		{
			write(1, (*env)[j], var_name + 1);
			write(1, "\"", 1);
			write(1, &(*env)[j][var_name + 1],
				ft_strlen((*env)[j]) - (var_name + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, (*env)[j], ft_strlen((*env)[j]));
			write(1, "\n", 1);
		}
		j++;
	}
	return (0);
}

int	ft_export(char **argv, char ***env)
{
	if (!argv[1])
		export_no_arg(env);
	return (export_arg(argv, env));
}
