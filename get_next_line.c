/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:24 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/27 02:06:50 by yael-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#define BUFFER_SIZE 42
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

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i = 0;

	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	char	*s3_start;
	size_t	len1 = ft_strlen(s1);
	size_t	len2 = ft_strlen(s2);

	s3 = (char *)malloc(len1 + len2 + 1);
	if (!s3)
		return (NULL);
	s3_start = s3;
	while (*s1)
		*s3++ = *s1++;
	while (*s2)
		*s3++ = *s2++;
	*s3 = '\0';
	return (s3_start);
}
size_t	ft_strlen(const char *s)
{
	size_t	size = 0;
	while (s[size])
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
	return (c - sizem);
} */
char	*extractor(char *breader);
char	*get_next_line(int fd);
void	*ft_free(char *temp, char *btemp);
char	*extractor_restante(char *breader);

int main(void)
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
char	*get_next_line(int fd)
{
	static char	*breader;
	ssize_t		read_bytes;
	char		*line;
	char		*temp;
	char 		*bcopy;

	if (!breader)
		breader = ft_strdup("");
	read_bytes = 1;
	temp = (char *)malloc(BUFFER_SIZE + 1);
	while (!ft_strchr(breader,'\n') && read_bytes > 0 )
	{
		read_bytes = read(fd, temp, BUFFER_SIZE);
		if (read_bytes < 0 || !temp )
			return (ft_free(breader,temp),NULL);
		temp[read_bytes] = '\0';
		bcopy = ft_strjoin(breader,temp);
		free(breader);
		breader = bcopy;
	}
	line = extractor(breader);
	bcopy = extractor_restante(breader);
	free(breader);
	breader = bcopy;
	return (free(temp),line);
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

void	*ft_free(char *temp, char *btemp)
{
	free(temp);
	free(btemp);
} 
