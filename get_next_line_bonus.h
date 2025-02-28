/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:57:23 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/28 13:37:22 by yael-you         ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#ifndef BUFFER_SIZE
    #define BUFFER_SIZE 42
#endif
#ifndef MAX_FD
# define MAX_FD 1024 // Límite máximo de descriptores de archivo
#endif
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strncpy(char *dest, char *src, unsigned int n);
char	*ft_strdup(const char *s);
char	*get_next_line(int fd);

