/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 23:42:11 by oessamdi          #+#    #+#             */
/*   Updated: 2022/07/04 03:52:23 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line(char *s)
{
	int		i;
	char	*line;

	i = 0;
	if (!s[i])
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_strlcpy(line, s, i + 1);
	return (line);
}

char	*get_rest(char *s)
{
	int		i;
	int		len;
	char	*rest;

	i = 0;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	len = ft_strlen(s);
	rest = malloc(len - i + 1);
	if (!rest)
		return (NULL);
	ft_strlcpy(rest, s + i, len - i + 1);
	free(s);
	return (rest);
}

char	*read_line(int fd, char *rest)
{
	int			checkr;
	char		*tmp;

	checkr = 1;
	tmp = malloc(BUFFER_SIZE + 1);
	if (!tmp)
		return (NULL);
	while (!ft_strchr(rest, '\n') && checkr != 0)
	{
		checkr = read(fd, tmp, BUFFER_SIZE);
		if (checkr == -1)
		{
			free(tmp);
			return (0);
		}
		tmp[checkr] = '\0';
		rest = ft_strjoin(rest, tmp);
	}
	free(tmp);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest[fd] = read_line(fd, rest[fd]);
	if (!rest[fd])
		return (NULL);
	line = get_line(rest[fd]);
	rest[fd] = get_rest(rest[fd]);
	return (line);
}
