void test_invalid_fd(void) {
    char *line;

    // Prueba con un fd inválido (menos de 0)
    line = get_next_line(-1);  // fd inválido
    if (line == NULL) {
        printf("Test 1 (fd -1): OK\n");
    } else {
        printf("Test 1 (fd -1): Failed, line = %s\n", line);
        free(line);
    }

    // Prueba con un fd cerrado
    int fd = open("test.txt", O_RDONLY);
    close(fd);
    line = get_next_line(fd);  // fd cerrado
    if (line == NULL) {
        printf("Test 2 (fd cerrado): OK\n");
    } else {
        printf("Test 2 (fd cerrado): Failed, line = %s\n", line);
        free(line);
    }

    // Prueba con un fd inválido (un número arbitrario grande)
    line = get_next_line(100);  // fd fuera de rango
    if (line == NULL) {
        printf("Test 3 (fd 100): OK\n");
    } else {
        printf("Test 3 (fd 100): Failed, line = %s\n", line);
        free(line);
    }

    // Simulando un fallo en la llamada a read()
    line = get_next_line(0);  // Con stdin, pero forzamos el error de read()
    if (line == NULL) {
        printf("Test 4 (read error): OK\n");
    } else {
        printf("Test 4 (read error): Failed, line = %s\n", line);
        free(line);
    }
}

void test_empty_or_newline_file(void) {
    char *line;

    // Crear archivo vacío
    FILE *file = fopen("empty.txt", "w");
    fclose(file);

    // Probar con un archivo vacío
    int fd = open("empty.txt", O_RDONLY);
    line = get_next_line(fd);
    if (line == NULL) {
        printf("Test 1 (archivo vacío): OK\n");
    } else {
        printf("Test 1 (archivo vacío): Failed, line = %s\n", line);
        free(line);
    }
    close(fd);

    // Crear archivo con solo saltos de línea
    file = fopen("newline_only.txt", "w");
    fprintf(file, "\n\n\n\n");
    fclose(file);

    // Probar con un archivo que solo tiene saltos de línea
    fd = open("newline_only.txt", O_RDONLY);
    line = get_next_line(fd);
    if (line != NULL && strcmp(line, "\n") == 0) {
        printf("Test 2 (solo saltos de línea): OK\n");
    } else {
        printf("Test 2 (solo saltos de línea): Failed, line = %s\n", line);
        free(line);
    }
    close(fd);
}

void test_read_after_free(void) {
    char *line;
    int fd = open("test.txt", O_RDONLY);

    line = get_next_line(fd);
    printf("Linea leída antes de liberar: %s\n", line);
    free(line);

    // Ahora intentamos leer después de liberar, lo que debe producir un fallo o comportamiento indefinido
    line = get_next_line(fd);
    if (line == NULL) {
        printf("Test 1 (leer después de free): OK\n");
    } else {
        printf("Test 1 (leer después de free): Failed, line = %s\n", line);
        free(line);
    }
    close(fd);
}

int main() {
    // Test de fd inválidos
    test_invalid_fd();

    // Test con archivo vacío o solo con saltos de línea
    test_empty_or_newline_file();

    // Test de leer después de hacer free()
    test_read_after_free();

    return 0;
}