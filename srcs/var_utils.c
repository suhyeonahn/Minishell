/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:35:53 by suahn             #+#    #+#             */
/*   Updated: 2022/03/28 16:35:55 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_value(char **env, char *name)
{
	int	i;
	int	len;

	len = ft_strlen(name);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(name, env[i], len))
		{
			free(name);
			return (ft_substr(env[i], len + 1,
					ft_strlen(env[i]) - len - 1));
		}
		i++;
	}
	free(name);
	return (NULL);
}

char	**add_var_no_env(char *var)
{
	char	**tmp;

	tmp = malloc(sizeof(char *) * 2);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_strcpy(var);
	tmp[1] = 0;
	return (tmp);
}

char	**add_var(char **env, char *var)
{
	char	**tmp;
	int		i;

	if (!env)
		return (add_var_no_env(var));
	i = 0;
	while (env && env[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 2));
	if (!tmp)
		return (NULL);
	tmp[i + 1] = 0;
	i = 0;
	while (env && env[i])
	{
		tmp[i] = ft_strcpy(env[i]);
		i++;
	}
	tmp[i] = ft_strcpy(var);
	free_var(env);
	return (tmp);
}

char	**delete_var(char **env, char *var)
{
	char	**new;
	int		i;
	int		j;

	j = 0;
	while (env && env[j])
		j++;
	new = malloc(sizeof(char *) * j);
	if (!new)
		return (NULL);
	new[j - 1] = 0;
	i = 0;
	j = 0;
	while (env && env[j])
	{
		if (ft_strncmp(var, env[j], ft_strlen(var)))
		{
			new[i] = ft_strcpy(env[j]);
			i++;
		}
		j++;
	}
	i = 0;
	free_var(env);
	return (new);
}

void	free_var(char **var)
{
	int	i;

	i = 0;
	while (var[i])
	{
		free(var[i]);
		i++;
	}
	free(var[i]);
	free(var);
}
