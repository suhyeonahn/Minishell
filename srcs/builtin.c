/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:36:54 by suahn             #+#    #+#             */
/*   Updated: 2022/03/28 14:15:43 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_echo_flag(char **argv)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 1;
	j = 0;
	while (argv[i] && argv[i][j])
	{
		if (argv[i][j++] == '-')
		{
			while (argv[i][j] == 'n')
				j++;
			if (argv[i][j] == '\0')
				++count;
			else
				return (count);
		}
		else
			return (count);
		i++;
		j = 0;
	}
	return (count);
}

int	ft_echo(char **argv)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	i += check_echo_flag(argv);
	if (i > 1)
		flag = 1;
	while (argv && argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int	ft_pwd(void)
{
	char	s[100];

	getcwd(s, 100);
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
	g_sig.exit_status = 0;
	return (0);
}

int	ft_env(char ***env)
{
	char	**envp;

	envp = (*env);
	while (*envp != 0)
	{
		if (has_equal(*envp))
		{
			write(1, *envp, ft_strlen(*envp));
			write(1, "\n", 1);
		}
		envp++;
	}
	return (0);
}

int	ft_unset(char **argv, char ***env)
{
	int	i;
	int	j;
	int	ret;

	if (!argv[1])
		return (0);
	i = 1;
	while (argv && argv[i])
	{
		ret = check_var_name(argv[i]);
		if (ret == 1 || ret == -1)
			return (builtin_error_msg("unset", argv[i]));
		j = 0;
		while ((*env) && (*env)[j])
		{
			if (!ft_strncmp(argv[i], (*env)[j], ft_strlen(argv[i])))
			{
				(*env) = delete_var((*env), argv[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
