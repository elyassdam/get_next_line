#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

#define BUFFER_SIZE 42
char	*extractor(char *breader);
char	*get_next_line(int fd);
void	*ft_free(char *temp, char *btemp);

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
	static char	breader[BUFFER_SIZE + 1];
	ssize_t		read_bytes;
	char		*btemp;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(breader, '\n') && read_bytes > 0)
	{
		btemp = (char *)malloc(BUFFER_SIZE + 1);
		if (!btemp)
			return (NULL);
		read_bytes = read(fd, btemp, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(btemp), NULL);
		btemp[read_bytes] = '\0';
		temp = ft_strjoin(breader, btemp);
		if (!temp)
			return (free(btemp),NULL);
		ft_strncpy(breader, temp, ft_strlen(temp) + 1);
		ft_free(temp,btemp);
	}
	return (line = extractor(breader), line);
}

void	*ft_free(char *temp, char *btemp)
{
	free(temp);
	free(btemp);
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


