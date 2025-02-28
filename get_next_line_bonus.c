#include <unistd.h>
#include <stdlib.h>

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

#ifndef MAX_FD
# define MAX_FD 1024 // Límite máximo de descriptores de archivo
#endif

char    *ft_strchr(const char *s, int c);
char    *ft_strdup(const char *s);
char    *ft_strjoin(char const *s1, char const *s2);
char    *extractor(char *breader);
char    *extractor_restante(char *breader);
void    ft_free(char **breader, char **temp);

void	ft_free(char **breader, char **temp)
{
	if (*breader)
	{
		free (*breader);
		*breader = NULL;
	}
	if (*temp)
	{
		free(*temp);
		*temp = NULL;
	}
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

char *get_next_line_bonus(int fd) {
    
    static char *breaders[MAX_FD]; // Array estático para breader por fd
    ssize_t read_bytes;
    char *line;
    char *temp;
    char *bcopy;

    if (fd < 0 || fd >= MAX_FD)
        return NULL;

    if (!breaders[fd])
        breaders[fd] = ft_strdup("");

    read_bytes = 1;
    while (!ft_strchr(breaders[fd], '\n') && read_bytes > 0) {
        temp = (char *)malloc(BUFFER_SIZE + 1);
        if (!temp)
            return (free(temp), NULL);
        read_bytes = read(fd, temp, BUFFER_SIZE);
        if (read_bytes < 0)
            return (ft_free(&breaders[fd], &temp), NULL);
        temp[read_bytes] = '\0';
        bcopy = ft_strjoin(breaders[fd], temp);
        ft_free(&breaders[fd], &temp);
        if (!bcopy) {
            breaders[fd] = NULL;
            return NULL;
        }
        breaders[fd] = bcopy;
    }

    line = extractor(breaders[fd]);
    bcopy = extractor_restante(breaders[fd]);
    free(breaders[fd]);
    breaders[fd] = bcopy;
    return (line);
}
/* int main() {
    int fd1, fd2, fd3, fd4;
    char *line;

    // Abrir archivos de prueba (asegúrate de que existan)
    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);
    fd3 = open("file3.txt", O_RDONLY);
    fd4 = open("file4.txt", O_RDONLY);

    if (fd1 < 0 || fd2 < 0 || fd3 < 0 || fd4 < 0) {
        perror("Error opening files");
        return 1;
    }

    // Leer líneas de los archivos
    while ((line = get_next_line_bonus(fd1)) != NULL) {
        printf("fd1: %s", line);
        free(line);
    }

    while ((line = get_next_line_bonus(fd2)) != NULL) {
        printf("fd2: %s", line);
        free(line);
    }

    while ((line = get_next_line_bonus(fd3)) != NULL) {
        printf("fd3: %s", line);
        free(line);
    }
    while ((line = get_next_line_bonus(fd4)) != NULL) {
        printf("fd4: %s", line);
        free(line);
    }

    // Cerrar archivos
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);

    return 0;
} */