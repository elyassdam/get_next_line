/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:24 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/27 15:27:47 by yael-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <string.h>

/* char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s);
	return (NULL);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	res ;
	void	*ptr;
	char	*str;

	res = nmemb * size;
	if ((nmemb != 0) && (res / nmemb != size))
		return (NULL);
	ptr = (char *)malloc(res);
	if (!ptr)
		return (NULL);
	str = (char *)ptr;
	while (res--)
		*str++ = 0;
	return (ptr);
}
f (!breader)	dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
} int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); 
		free(line);
	}

	close(fd); // Cerrar el archivo
	return (0);
}  
f (!breader)
	s3 = (char *)malloc(len1 + len2 + 1);
	if (!s3)
		return (NULL);
	s3_start = s3;ññ
	while (*s1)
		*s3++ = *s1++;
	while (*s2)
		*s3++ = *s2++;ññ
size_t	ft_strlen(const char *s)
{
	size_t	size = 0;
	while (s[size]) int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error al abrir el archivo");
		return (1);
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line); 
		free(line);
	}

	close(fd); // Cerrar el archivo
	return (0);
}  
		size++;
	return (size);
}

char	*ft_strdup(const char *s)
{
	size_t	sizem;
	char	*c;

	sizem = ft_strlen(s);
	c = (char *)malloc(sizem + 1);
	if (!c)
		return (NULL);
	while (*s)
	{
		*c = *s;
		s++;
		c++;
	}
	*c = '\0';
	return (c - sizem);ññ
} */
char	*extractor(char *breader);
char	*get_next_line(int fd);
void	ft_free(char *temp, char *btemp);
char	*extractor_restante(char *breader);


char	*get_next_line(int fd)
{
	static char	*breader;
	ssize_t		read_bytes;
	char		*line;
	char		temp[BUFFER_SIZE + 1];
	char 		*bcopy;

	 if (!breader)
		breader = ft_strdup(""); 
	if (breader == NULL || fd < 0)
		return NULL;
	read_bytes = 1;
	while (!ft_strchr(breader,'\n') && read_bytes > 0 )
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes < 0)
			return (NULL);
		temp[read_bytes] = '\0';
		bcopy = ft_strjoin(breader,temp);
		free(breader);
		breader = bcopy;
	}
	line = extractor(breader);
	bcopy = extractor_restante(breader);
	free(breader);
	breader = bcopy;
	return (line);
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


int main(void)
{
	int fd = open("test.txt", O_RDONLY);
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
}   