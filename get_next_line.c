#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#define BUFFER_SIZE 42
char	*extractor(char *breader);
char	*get_next_line(int fd);

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("Error al abrir el archivo");
        return (1);
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) // Leer línea por línea
    {
        printf("%s", line); // Imprimir la línea leída
        free(line);         // Liberar memoria para la siguiente línea
    }

    close(fd); // Cerrar el archivo
    return (0);
} 

char	*get_next_line(int fd)
{
	static char	breader[BUFFER_SIZE + 1];
	ssize_t		read_bytes = 1;  
	char		*btemp;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);

	while (!ft_strchr(breader, '\n') && read_bytes > 0)
	{
		btemp = (char *)malloc(BUFFER_SIZE + 1);
		if (!btemp)
			return (NULL);

		read_bytes = read(fd, btemp, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(btemp);
			return (NULL);
		}
		btemp[read_bytes] = '\0';

		char *temp = ft_strjoin(breader, btemp);
		if (!temp)
		{
			free(btemp);
			return (NULL);
		}
		ft_strncpy(breader, temp, ft_strlen(temp) + 1);
		free(temp);
		free(btemp);
	}

	line = extractor(breader);
	return (line);
}

char	*extractor(char *breader)
{
	char	*start;
	char	*next;
	char	*line;

	if (!breader || !*breader)
		return (NULL);
    
	start = breader;
	next = breader;
	while (*next != '\0' && *next != '\n')
		next++;

	line = (char *)ft_calloc((next - start + 2), sizeof(char));
	if (!line)
		return (NULL);

	ft_strncpy(line, start, (next - start + 1));

	if (*next == '\n')
	{
		next++;
		ft_strncpy(breader, next, ft_strlen(next) + 1);  // ✅ Mueve correctamente el buffer
	}
	else
		breader[0] = '\0';  // ✅ Se asegura de vaciar el buffer al final del archivo

	return (line);
}


