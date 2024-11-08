#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
int main()
{
    const char *dirPath = "."; // Diretório atual
    DIR *dir = opendir(dirPath);

    if (dir == NULL) {
		printf("Erro ao abrir o arquivo: %s\n", strerror(errno));
        perror("Erro ao abrir diretório");
        return EXIT_FAILURE;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Ignorar entradas '.' e '..'
        if (entry->d_name[0] != '.') {
            printf("%s\n", entry->d_name);
        }
    }

    if (closedir(dir) == -1) {
        perror("Erro ao fechar diretório");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
*/
/*
int main()
{
    // Obtém o valor da variável de ambiente "HOME"
    char *home = getenv("HOME");
    if (home != NULL) {
        printf("O diretório home é: %s\n", home);
    } else {
        printf("A variável de ambiente HOME não está definida.\n");
    }

    // Obtém o valor da variável de ambiente "PATH"
    char *path = getenv("PATH");
    if (path != NULL) {
        printf("O PATH é: %s\n", path);
    } else {
        printf("A variável de ambiente PATH não está definida.\n");
    }

    return 0;
}
*/

#include <stdio.h>
#include <sys/stat.h>

int is_directory_valid(const char *path)
{
    struct stat path_stat;

    if (stat(path, &path_stat) != 0)
        return 0;
    return S_ISDIR(path_stat.st_mode);
}

void cd(char *dir)
{
    char	cwd[5000];
	char	*home;

	home = getenv("HOME");
	chdir(dir);

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n", cwd);
}

int main(int ac, char **av)
{
	cd(av[1]);
    return 0;
}
