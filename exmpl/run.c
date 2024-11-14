#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *path;
	char *home;

	// Obtém o valor da variável de ambiente "HOME"
    home = getenv("HOME");
    if (home != NULL) {
        printf("O diretório home é: %s\n", home);
    } else {
        printf("A variável de ambiente HOME não está definida.\n");
    }

    // Obtém o valor da variável de ambiente "PATH"
    path = getenv("PATH");
    if (path != NULL) {
        printf("O PATH é: %s\n", path);
    } else {
        printf("A variável de ambiente PATH não está definida.\n");
    }

    return 0;
}