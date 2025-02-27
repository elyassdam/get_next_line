/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:57:23 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/27 16:23:58 by yael-you         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stddef.h>
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 10000000
#endif
size_t	ft_strlen(const char *s);
char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strdup(const char *s);