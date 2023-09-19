/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:31:53 by suahn             #+#    #+#             */
/*   Updated: 2022/03/28 14:31:55 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	modify_cd_env(char ***env, char *old_pwd, char *s1)
{
	modify_oldpwd(env, old_pwd);
	modify_pwd(env, getcwd(s1, 100));
}

void	cd_argv(char **argv, char ***env, int *ret)
{
	char	*var;

	if (argv[1])
	{
		if (!ft_strcmp(argv[1], "-"))
		{
			var = get_var_value(*env, ft_strcpy("OLDPWD"));
			*ret = chdir(var);
			free(var);
			ft_pwd();
		}
		else
			*ret = chdir(argv[1]);
	}
	else
	{
		var = get_var_value(*env, ft_strcpy("HOME"));
		*ret = chdir(var);
		free(var);
	}
}

int	ft_cd(char **argv, char ***env)
{
	int		ret;
	char	s1[100];
	char	*old_pwd;

	ret = 0;
	old_pwd = getcwd(s1, 100);
	cd_argv(argv, env, &ret);
	if (ret == -1)
		return (builtin_error_msg("cd", argv[1]));
	else
		modify_cd_env(env, old_pwd, s1);
	return (0);
}
