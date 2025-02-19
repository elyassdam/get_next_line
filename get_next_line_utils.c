/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 17:04:24 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/19 17:27:54 by yael-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
size_t	ft_strlen(const char *s);

char	*ft_strchr(const char *s, int c)
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
	size_t	res = nmemb * size;
	void	*ptr;
	char	*str;

	if ((nmemb != 0) && (res / nmemb != size))
		return (NULL);
	ptr = (char *)malloc(res);
	if (!ptr)
		return (NULL);
	str = (char *)ptr;: 8 allocs, 8 frees, 1,161 bytes allocated
==467975== 
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i = 0;

	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';  // ✅ Asegura terminación en NULL
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