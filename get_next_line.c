/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-you <yael-you@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:15:35 by yael-you          #+#    #+#             */
/*   Updated: 2025/02/18 16:18:17 by yael-you         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

char *get_next_line(int fd)
{
	static char breader [BUFFER_SIZE];
	ssize_t read_bytes;
    char btemp;
	char *line;


	if (!fd || BUFFER_SIZE <= 0)
		return (NULL);
     read_bytes = read(fd, breader, BUFFER_SIZE);
	while((bytes_leidos = read(fd, buffer_temporal, BUFFER_SIZE)) > 0)
    {
        if (read_bytes < 0)
           return NULL;
        btemp [read_bytes] = '\0';
        breader = ft_strjoin(breader, btemp);
        if (!breadbef)
            return (NULL);
    }	
		
	
}