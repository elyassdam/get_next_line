/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:24 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/27 17:26:08 by yael-you         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
// void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return NULL;
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

/* void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	res ;
	void	*ptr;
	char	*str;

	res = nmemb * size;
	if ((nmemb != 0) && (res / nmemb != size))
		return (NULL);
	ptr = (char *)malloc(res);
	if (!ptr)4_LEAKS.KO
} */

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
	while (s1 && *s1)
		*s3++ = *s1++;
	while (s2 && *s2)
		*s3++ = *s2++;
	*s3 = '\0';
	return (s3_start);
}
size_t	ft_strlen(const char *s)
{
	size_t	size = 0;

	if(s == NULL)
		return 0;
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
}