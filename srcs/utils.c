/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 21:23:54 by suahn             #+#    #+#             */
/*   Updated: 2022/03/10 11:45:09 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_memcmp(void *s1, void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*s2;
	unsigned int	i;

	i = 0;
	if (!s || len <= 0 || (start > ft_strlen(s)))
		return (NULL);
	if (start > ft_strlen(s))
	{
		s2 = malloc(sizeof(char) * 1);
		if (!s2)
			return (NULL);
		s2[0] = '\0';
		return (s2);
	}
	s2 = malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (NULL);
	while (i < start)
	{
		i++;
		s++;
	}
	ft_strlcpy(s2, s, (len + 1));
	return (s2);
}

char	end_c(int quote)
{
	char	c;

	if (quote == 2)
		c = 34;
	else if (quote == 1)
		c = 39;
	else
		c = 0;
	return (c);
}

int	check_sign(const char *str, int *i, int *sign)
{
	if (str[*i] && (str[*i] == '-' || str[*i] == '+'))
	{
		if (str[*i] == '-' && str[*i + 1] && str[*i + 1] == '-' && !str[*i + 2])
			return (0);
		if ((str[*i + 1] && (str[*i + 1] == '-' || str[*i + 1] == '+'))
			|| !str[*i + 1])
			return (1);
		if (str[*i] == '-')
			*sign = *sign * -1;
		(*i)++;
	}
	return (1);
}

int	is_digit(const char *str)
{
	int					i;
	int					sign;
	unsigned long long	ret;
	int					check;

	i = 0;
	sign = 1;
	ret = 0;
	if (ft_strlen(&str[i]) > 19)
		return (1);
	check = check_sign(str, &i, &sign);
	if (!check)
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		ret = ret * 10 + str[i] - '0';
		i++;
	}
	if ((sign == -1 && ret > 9223372036854775808uLL)
		|| (sign == 1 && ret > LLONG_MAX))
		return (1);
	return (0);
}
