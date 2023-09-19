/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 10:38:08 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:42:01 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	ft_signal_handler(int sig_num)
{
	if (sig_num == SIGINT)
	{
		if (g_sig.pid == 1)
		{
			if (rl_on_new_line() == -1)
				exit(1);
			write(1, "\n", 1);
			rl_replace_line("", 1);
			rl_redisplay();
			g_sig.exit_status = 130;
			g_sig.sigint = 1;
		}
	}
}

static void	ft_signal_handler_hd(int sig_num)
{
	if (sig_num == SIGINT && !g_sig.pid)
	{
		rl_replace_line("", 1);
		g_sig.sigint_hd = 1;
		if (rl_on_new_line() == -1)
			exit(1);
		write(1, "\n", 1);
		exit(130);
	}
	if (sig_num == SIGQUIT && !g_sig.pid)
	{
		write(2, "Quit (core dumped)", 19);
		rl_replace_line("", 1);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
		if (rl_on_new_line() == -1)
			exit(1);
		write(1, "\n", 1);
		exit(131);
	}
}

void	check_signal_hd(void)
{
	signal(SIGQUIT, ft_signal_handler_hd);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ft_signal_handler_hd);
}

void	check_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, ft_signal_handler);
}
