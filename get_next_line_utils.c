/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffidha <ffidha@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 12:27:55 by ffidha            #+#    #+#             */
/*   Updated: 2023/12/16 10:29:30 by ffidha           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char )c)
			return ((char *)s + i);
		i++;
	}
	if (s[i] == (char )c)
		return ((char *) s + i);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*all;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;

	all = (char *)malloc(sizeof(char) *(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!all)
		return (NULL);
	while (s1[i])
	{
		all[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		all[i] = s2[j];
		j++;
		i++;
	}
	all[i] = '\0';
	return (all);
}
