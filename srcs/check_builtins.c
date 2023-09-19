/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:00:23 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:34:56 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	write_last_letter(char *str, char c, char **tmp)
{
	int	i;

	i = 0;
	while (str[i])
	{
		*tmp[i] = str[i];
		i++;
	}
	*tmp[i] = c;
	*tmp[i + 1] = '\0';
}

char	*write_line(char *str, char c)
{
	char	*tmp;

	if (!str)
	{
		tmp = malloc(2);
		if (!tmp)
			return (NULL);
		tmp[0] = c;
		tmp[1] = '\0';
		free(str);
		return (tmp);
	}
	tmp = malloc(ft_strlen(str) + 2);
	if (!tmp)
		return (NULL);
	write_last_letter(str, c, &tmp);
	free(str);
	return (tmp);
}

int	check_builtins(t_mini *mini, t_cmd *cmd, char ***env)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd->argv));
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(cmd->argv, env));
	if (!ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd->cmd, "export"))
		return (ft_export(cmd->argv, env));
	if (!ft_strcmp(cmd->cmd, "env"))
		return (ft_env(env));
	if (!ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(cmd->argv, env));
	if (!ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(mini, *env, cmd->argv));
	return (2);
}
