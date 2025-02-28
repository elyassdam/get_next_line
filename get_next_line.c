/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:24 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/28 13:41:21 by yael-you         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "get_next_line.h"

static char	*extractor(char *breader);
char		*get_next_line(int fd);
static void	ft_free(char **breader, char **temp);
static char	*extractor_restante(char *breader);

void	ft_free(char **breader, char **temp)
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
static char	*readline(int fd, char **breader, char **bcopy)
{
	ssize_t	read_bytes;
	char	*temp;

	read_bytes = 1;
	while (!ft_strchr(*breader, '\n') && read_bytes > 0)
	{
		temp = (char *)malloc(BUFFER_SIZE + 1);
		if (!temp)
			return (free(temp), NULL);
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes < 0)
			return (ft_free(breader, &temp), NULL);
		temp[read_bytes] = '\0';
		*bcopy = ft_strjoin(*breader, temp);
		ft_free(breader, &temp);
		if (!*bcopy)
			return (*breader = NULL, NULL);
		*breader = *bcopy;
	}
	return (*breader);
}

char	*get_next_line(int fd)
{
	static char	*breader;
	char		*line;
	char		*bcopy;

	if (fd < 0)
	{
		return (NULL);
	}
	if (!breader)
	{
		breader = ft_strdup("");
		if (!breader)
		{
			return (NULL);
		}
	}
	breader = readline(fd, &breader, &bcopy);
	line = extractor(breader);
	bcopy = extractor_restante(breader);
	return (free(breader), breader = bcopy, line);
}

char	*extractor(char *breader)
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

char	*extractor_restante(char *breader)
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
/*
int	main(void)
{
	int fd = open("get_next_line_bonus.h", O_RDONLY);

	char *line;
	// free(get_next_line(fd));
	while ((line = get_next_line(fd)) != NULL)
	{
		// printf("No deberia\n");
		printf("%s", line);
		free(line);
	}
	// line = get_next_line(fd);
	free(line);

	close(fd); // Cerrar el archivo
	return (0);
} */