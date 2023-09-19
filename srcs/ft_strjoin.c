/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 04:31:43 by suahn             #+#    #+#             */
/*   Updated: 2022/04/04 04:31:44 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*s3;
	size_t	dstsize;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dstsize = ft_strlen(s2) + ft_strlen(s1);
	s3 = malloc(sizeof(char) * dstsize + 1 + 1);
	if (!s3)
		return (NULL);
	while (*s1)
	{
		s3[i++] = *s1++;
	}
	while (*s2)
	{
		s3[i++] = *s2++;
	}
	s3[i] = '\n';
	s3[i + 1] = '\0';
	return ((char *)s3);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	dstsize;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	dstsize = ft_strlen(s2) + ft_strlen(s1);
	s3 = malloc(sizeof(char) * dstsize + 1);
	if (!s3)
		return (NULL);
	while (*s1)
	{
		s3[i++] = *s1++;
	}
	while (*s2)
	{
		s3[i++] = *s2++;
	}
	s3[i] = '\0';
	return ((char *)s3);
}
