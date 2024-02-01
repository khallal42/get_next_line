/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khallal <khallal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:54:11 by khallal           #+#    #+#             */
/*   Updated: 2022/11/10 15:20:48 by khallal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*getf(char *p)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (p[i] != '\n' && p[i] != '\0')
		i++;
	if (p[i++] == '\0')
	{
		free(p);
		return (NULL);
	}
	while (p[i + j] != '\0')
		j++;
	s = malloc(j + 1);
	if (!s)
		return (NULL);
	j = 0;
	while (p[i] != '\0')
		s[j++] = p[i++];
	s[j] = '\0';
	free(p);
	return (s);
}

char	*get_line(char *h)
{
	char	*p;
	int		i;

	i = 0;
	if (!h)
		return (NULL);
	while (h[i] != '\n' && h[i])
		i++;
	p = malloc(i + 2);
	if (!p)
		return (NULL);
	i = 0;
	while (h[i] && h[i] != '\n')
	{
		p[i] = h[i];
		i++;
	}
	if (h[i] == '\n')
	{
		p[i] = h[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*get_next(int fd, char *h)
{
	char	*p;
	int		i;

	i = 1;
	p = ft_calloc((BUFFER_SIZE + 1), 1);
	if (!p)
		return (NULL);
	while (!ft_strchr(h, '\n') && i != 0)
	{
		i = read(fd, p, BUFFER_SIZE);
		if (i == -1)
		{
			free(p);
			free(h);
			return (0);
		}
		p[i] = '\0';
		h = ft_strjoin(h, p);
	}
	free(p);
	return (h);
}

char	*get_next_line(int fd)
{
	static char	*k[OPEN_MAX];
	char		*j;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	k[fd] = get_next(fd, k[fd]);
	if (!k[fd])
	{
		free(k[fd]);
		return (NULL);
	}
	j = get_line(k[fd]);
	k[fd] = getf(k[fd]);
	if (j[0] == '\0')
	{
		free(j);
		return (NULL);
	}
	return (j);
}
