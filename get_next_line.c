/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oessamdi <oessamdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 23:42:11 by oessamdi          #+#    #+#             */
/*   Updated: 2021/12/11 10:31:46 by oessamdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest = read_line(fd, rest);
	if (!rest)
		return (NULL);
	line = get_line(rest);
	rest = get_rest(rest);
	return (line);
}
