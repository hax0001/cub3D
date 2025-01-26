/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akajjou <akajjou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:56:47 by nait-bou          #+#    #+#             */
/*   Updated: 2025/01/26 19:35:27 by akajjou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*keep_b(char *buf)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		return (NULL);
	}
	str = (char *)ft_malloc(ft_strlen(buf) - i++ + 1);
	if (!str)
		return (NULL);
	while (buf[i])
	{
		str[j] = buf[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (buf = NULL, str);
}

static char	*final_r(char *buf)
{
	char	*str;
	int		i;

	if (!buf[0])
		return (NULL);
	if (!ft_strchr(buf, '\n'))
		return (ft_strdup(buf));
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	str = (char *)ft_malloc(i + 2);
	if (!str)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		str[i] = buf[i];
		i++;
	}
	if (buf[i] && buf[i] == '\n')
	{
		str[i] = '\n';
		str[i + 1] = '\0';
	}
	return (str);
}

static char	*joinb(char *s1, char *s2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	return (str);
}

static char	*read_fd(int fd, char *buffer)
{
	char	*tmp;
	int		br;

	br = 1;
	if (!buffer)
	{
		buffer = (char *)ft_malloc(1);
		buffer[0] = '\0';
	}
	tmp = (char *)ft_malloc((size_t)BUFFER_SIZE + 1);
	while (br > 0)
	{
		br = read(fd, tmp, BUFFER_SIZE);
		if (br == -1)
			return (NULL);
		tmp[br] = '\0';
		buffer = joinb(buffer, tmp);
		if (ft_strchr(tmp, '\n'))
			break ;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (buf = NULL, NULL);
	buf = read_fd(fd, buf);
	if (!buf)
		return (NULL);
	line = final_r(buf);
	buf = keep_b(buf);
	return (line);
}
