/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:25:55 by yael-you          #+#    #+#             */
/*   Updated: 2025/03/03 14:34:19 by yael-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	ft_free(char **breader, char **temp)
{
	if (*breader)
	{
		free(*breader);
		*breader = NULL;
	}
	if (*temp)
	{
		free(*temp);
		*temp = NULL;
	}
}

static char	*extractor(char *breader)
{
	char	*ptr;
	char	*line;

	if (!breader || !*breader)
		return (NULL);
	ptr = breader;
	while (*ptr && *ptr != '\n')
		ptr++;
	line = (char *)malloc((ptr - breader) + (*ptr == '\n') + 1);
	if (!line)
		return (NULL);
	ft_strncpy(line, breader, (ptr - breader) + (*ptr == '\n'));
	return (line);
}

static char	*extractor_left(char *breader)
{
	char	*ptr;
	char	*resto;

	if (!breader || !*breader)
		return (NULL);
	ptr = breader;
	while (*ptr && *ptr != '\n')
		ptr++;
	if (*ptr == '\n')
		ptr++;
	if (!*ptr)
		return (NULL);
	resto = ft_strdup(ptr);
	return (resto);
}

static char	*readline(int fd, char **breaders, char **bcopy)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = 1;
	while (!ft_strchr(*breaders, '\n') && read_bytes > 0)
	{
		temp = (char *)malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (free(temp), NULL);
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes < 0)
			return (ft_free(breaders, &temp), NULL);
		temp[read_bytes] = '\0';
		*bcopy = ft_strjoin(*breaders, temp);
		ft_free(breaders, &temp);
		if (!*bcopy)
		{
			*breaders = NULL;
			return (NULL);
		}
		*breaders = *bcopy;
	}
	return (*breaders);
}

char	*get_next_line(int fd)
{
	static char	*breaders[MAX_FD];
	char		*line;
	char		*bcopy;

	if (fd < 0 || fd >= MAX_FD)
		return (NULL);
	if (!breaders[fd])
		breaders[fd] = ft_strdup("");
	breaders[fd] = readline(fd, &breaders[fd], &bcopy);
	line = extractor(breaders[fd]);
	bcopy = extractor_left(breaders[fd]);
	free(breaders[fd]);
	breaders[fd] = bcopy;
	return (line);
}