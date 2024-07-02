/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftome-ve <ftome-ve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 20:03:58 by ftome-ve          #+#    #+#             */
/*   Updated: 2024/05/22 16:48:53 by ftome-ve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
	{
		*ptr++ = 0;
	}
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*str2;
	size_t	i;

	i = 0;
	len = ft_strlen(str);
	str2 = ft_calloc(len, sizeof(char));
	if (str2 == NULL)
	{
		free (str2);
		return (NULL);
	}
	else
	{
		while (i < len)
		{
			str2[i] = str[i];
			i++;
		}
		str2[i] = '\0';
	}
	return (str2);
}

char	*funtion_read( char *line, int fd)
{
	char	*buffer;
	int		size_read;
	char	*temp;

	buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	size_read = 1;
	while (size_read > 0 && !ft_strchr(buffer, '\n'))
	{
		size_read = read(fd, buffer, BUFFER_SIZE);
		if (size_read == -1)
		{
			free (buffer);
			return (NULL);
		}
		buffer[size_read] = '\0';
		temp = ft_strjoin(line, buffer);
		free (line);
		line = temp;
	}
	free (buffer);
	return (line);
}

char	*ft_nextline(char *line)
{
	char	*magic;
	char	*final;
	char	*tmp;

	tmp = NULL;
	if (ft_strchr(line, '\n'))
	{
		magic = ft_strchr(line, '\n');
		final = tmp;
		tmp = ft_strdup(&magic[1]);
		if (final)
			free (final);
		ft_bzero(&magic[1], ft_strlen(magic));
		if (ft_strlen(tmp) == 0)
		{
			free(tmp);
			tmp = NULL;
		}
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*final[OPEN_MAX]];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		if (ft_strlen(final[fd]) > 0)
		{
			free (final[fd]);
			final[fd] = NULL;
		}
		return (NULL);
	}
	if (ft_strlen(final[fd]) > 0)
	{
		line = ft_strdup(final[fd]);
		free (final[fd]);
		final[fd] = NULL;
	}
	else
		line = ft_calloc(1, sizeof(char));
	line = funtion_read(line, fd);
	final[fd] = ft_nextline(line);
	if (!line || ft_strlen(line) <= 0 || line == NULL)
		return (free (line), NULL);
	return (line);
}
