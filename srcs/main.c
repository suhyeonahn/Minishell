/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:00:12 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:16:30 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_sig	g_sig;

void	exit_with_message(t_mini *mini, char **env, int ret, char *message)
{
	free_t_mini(mini);
	free_env(env);
	write(2, message, ft_strlen(message));
	rl_clear_history();
	exit(ret);
}

void	sig_init(void)
{
	g_sig.sigint_hd = 0;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 1;
	g_sig.exit_status = 0;
}

void	prompt_line(t_mini *mini, char **env)
{
	rl_outstream = stderr;
	if (mini->line != NULL)
		free(mini->line);
	mini->line = readline("\e[0;32mminishell $\e[0m ");
	if (!mini->line)
	{
		(void)env;
		exit_with_message(mini, env, 0, "exit\n");
	}
	g_sig.sigint_hd = 0;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.has_child = 0;
}

void	setting(char **env, char ***new_env)
{
	struct termios	new;

	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &new);
	check_signal();
	*new_env = init_new_env_table(env);
	modify_shlvl(new_env);
	sig_init();
}

int	main(int argc, char **argv, char **env)
{
	t_mini			*mini;
	char			**new_env;

	(void)argc;
	(void)argv;
	setting(env, &new_env);
	mini = new_t_mini();
	while (1)
	{
		prompt_line(mini, new_env);
		g_sig.syntax_error = 0;
		mini->ret = 0;
		if (ft_strlen(mini->line) > 0)
		{
			add_history(mini->line);
			if (parse_commands(mini, new_env) == 0)
			{
				if (mini->ret == 0 && g_sig.syntax_error != 1)
					exec_commands(mini, &new_env);
				free_t_cmd_list(mini->cmds);
				mini->cmds = NULL;
			}
		}
	}
}
