/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:41:34 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:54:49 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	round_return_code(long long *return_code)
{
	if (*return_code < 0)
	{
		while (*return_code < 100000000000000)
				*return_code += 256 * 300000000000;
		while (*return_code < INT_MIN)
			*return_code += 256 * 8000000;
		while (*return_code < 0)
			*return_code += 256;
	}
	else if (*return_code > 255)
	{
		while (*return_code > 100000000000000)
			*return_code -= 256 * 300000000000;
		while (*return_code > INT_MAX)
			*return_code -= 256 * 8000000;
		while (*return_code > 255)
			*return_code -= 256;
	}
}

void	apply_return_code(t_mini *mini, char **env, char *argv)
{
	long long	return_code;

	return_code = ft_atoi_for_exit(argv);
	if (return_code >= 0 && return_code <= 255)
	{
		g_sig.exit_status = return_code;
		free_t_mini(mini);
		free_env(env);
		exit(g_sig.exit_status);
	}
	round_return_code(&return_code);
	g_sig.exit_status = return_code;
	free_t_mini(mini);
	free_env(env);
	exit(g_sig.exit_status);
}

int	exit_arg_error(void)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: too many arguments\n", 36);
	g_sig.exit_status = 1;
	return (1);
}

int	ft_exit(t_mini *mini, char **env, char **argv)
{
	if (argv[1])
	{
		if (is_digit(argv[1]))
		{
			write(2, "minishell: exit: ", 17);
			write(2, argv[1], ft_strlen(argv[1]));
			write(2, ": numeric argument required\n", 28);
			g_sig.exit_status = 2;
			free_t_mini(mini);
			free_env(env);
			exit(g_sig.exit_status);
		}
		if (argv[2])
			return (exit_arg_error());
		apply_return_code(mini, env, argv[1]);
	}
	free_t_mini(mini);
	free_env(env);
	exit(g_sig.exit_status);
}
