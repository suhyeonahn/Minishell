/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 02:26:23 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 02:26:24 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strnstr(char *haystack, char *needle, size_t len)
{
	size_t	len_nd;

	len_nd = ft_strlen(needle);
	if (haystack == NULL)
		return (NULL);
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len-- >= len_nd)
	{
		if (*haystack == *needle && !(ft_memcmp(haystack, needle, len_nd)))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

char	*find_path_routine(t_find_path *fp, char **env)
{
	while (ft_strnstr(env[fp->i], "PATH", 4) == 0)
	{
		if (!env[fp->i])
			return (NULL);
		fp->i++;
	}
	return ("SUCCESS");
}

char	*find_path(char *cmd, char **env)
{	
	t_find_path	fp;
	struct stat	sb;

	fp.i = 0;
	if (find_path_routine(&fp, env) == NULL)
		return (NULL);
	fp.paths = ft_split(env[fp.i] + 5, ':');
	fp.i = 0;
	while (fp.paths[fp.i])
	{
		fp.part_path = ft_strjoin(fp.paths[fp.i], "/");
		fp.path = ft_strjoin(fp.part_path, cmd);
		free(fp.part_path);
		if (fp.path && (stat(fp.path, &sb) == 0 && sb.st_mode & S_IXUSR))
		{
			free_strarr(fp.paths);
			return (fp.path);
		}
		free(fp.path);
		fp.i++;
	}
	free_strarr(fp.paths);
	return (NULL);
}

int	has_pipe(t_cmd_node *cmds)
{
	if (cmds->next != NULL)
		return (1);
	else
		return (0);
}

int	find_slash(char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
		return (-1);
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
