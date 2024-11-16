#include <term.h>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <curses.h>
#include <termios.h> 	
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/resource.h>

/*
int main() 
{
    char *argv[] = {"/bin/ls", "-l", "/home", NULL}; // Argumentos para o novo programa
    char *envp[] = {NULL}; // Ambiente para o novo programa

    printf("Executando ls -l /home usando execve\n");

    // Executa o novo programa
    if (execve("/bin/ls", argv, envp) == -1) {
        perror("Erro ao executar execve");
        exit(EXIT_FAILURE);
    }

    // Este código não será executado se execve for bem-sucedido
    printf("Este código não será executado.\n");

    return 0;
}
*/
/*
// ex 1
int main()
{
    pid_t pid;

	pid = fork(); // Cria um novo processo
    if (pid < 0) 
	{
        // Erro ao criar o processo filho
        perror("Falha no fork");
        return 1;
    } else if (pid == 0)
	{
        // Este bloco é executado pelo processo filho
        printf("Processo filho: PID = %d, PPID = %d\n", getpid(), getppid());
    } else
	{
        // Este bloco é executado pelo processo pai
        printf("Processo pai: PID = %d, PID do filho = %d\n", getpid(), pid);
    }
    return 0;
}
*/
/*
// ex 2
int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Falha no fork");
        return 1;
    } else if (pid == 0) {
        // Processo filho: imprime números pares
        for (int i = 0; i <= 10; i += 2) {
            printf("Filho: %d\n", i);
            sleep(1); // Pausa para simular processamento
        }
    } else {
        // Processo pai: imprime números ímpares
        for (int i = 1; i <= 10; i += 2) {
            printf("Pai: %d\n", i);
            sleep(1); // Pausa para simular processamento
        }
    }
    return 0;
}
*/
/*
//exe: 3
int main() {
    pid_t pid = fork(); // Criação do processo filho

    if (pid < 0) {
        // Verificação de erro no fork
        perror("Erro ao criar o processo filho");
        return 1;
    } else if (pid == 0) {
        // Código do processo filho
        printf("Processo filho iniciado. PID = %d\n", getpid());
        sleep(1); // Simula algum processamento no processo filho
        printf("Processo filho terminando.\n");
        return 42; // Código de saída do processo filho
    } else {
        // Código do processo pai
        int status;
        printf("Processo pai aguardando o término do processo filho.\n");
        
        // wait() faz o pai aguardar o término do processo filho
        wait(&status);

        // Verifica se o processo filho terminou com sucesso
        if (WIFEXITED(status)) {
            printf("Processo filho terminou com código de saída %d\n", WEXITSTATUS(status));
        } else {
            printf("Processo filho terminou de forma anormal.\n");
        }

        printf("Processo pai continuando sua execução.\n");
    }

    return 0;
}
*/
/*
int main()
{
    int pipefd[2]; // Array para armazenar os descritores do pipe (0 para leitura, 1 para escrita)
    pid_t pid;
    char buffer[100]; // Buffer para armazenar a mensagem recebida

    // Criação do pipe
    if (pipe(pipefd) == -1)
	{
        perror("Erro ao criar o pipe");
        return 1;
    }

    // Criação do processo filho
    pid = fork();

    if (pid < 0)
	{
        perror("Erro ao criar o processo filho");
        return 1;
    }
	else if (pid == 0)
	{
        // Código do processo filho
        close(pipefd[0]); // Fecha a extremidade de leitura do pipe no processo filho

        char mensagem[] = "Olá, este é o processo filho!";
        write(pipefd[1], mensagem, strlen(mensagem) + 1); // Escreve a mensagem no pipe
        close(pipefd[1]); // Fecha a extremidade de escrita após enviar a mensagem

        printf("Processo filho: mensagem enviada ao processo pai.\n");
        return 0; // O processo filho termina
    }
	else
	{
        // Código do processo pai
        close(pipefd[1]); // Fecha a extremidade de escrita do pipe no processo pai

        // Espera que o processo filho termine
        wait(NULL);

        // Lê a mensagem enviada pelo processo filho
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Processo pai recebeu a mensagem: %s\n", buffer);

        close(pipefd[0]); // Fecha a extremidade de leitura após a leitura
    }

    return 0;
}
*/
/*
// Manipulador de sinal para SIGINT
void handle_sigint(int sig) {
    // Substitui a linha atual por uma mensagem padrão
    rl_replace_line("Mensagem padrão após Ctrl+C", 1); // troca a linha atual escrita por esta llinha
    // Redesenha o prompt com a nova linha
    rl_redisplay();
}

int main() {
    // Define o manipulador de sinal para SIGINT
    signal(SIGINT, handle_sigint);

    while (1) {
        // Prompt para o usuário
        char *input = readline("Digite algo: ");
        
        // Sai do loop se readline retornar NULL (Ctrl+D)
        if (input[0] == '.') {
            printf("\nSaindo...\n");
            break;
        }

        // Adiciona a entrada ao histórico
        add_history(input);

        // Exibe a entrada digitada
        printf("Você digitou: %s\n", input);

        // Libera a memória alocada
        free(input);
    }
    return 0;
}
*/
/*
int main()
{
    pid_t pid = fork();  // Cria um processo filho

    if (pid == -1) {
        // Caso ocorra um erro no fork
        perror("Erro ao criar o processo filho");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        // Código do processo filho
        printf("Processo filho (PID: %d) está executando...\n", getpid());
        sleep(2);  // Simula trabalho do processo filho
        printf("Processo filho (PID: %d) finalizando...\n", getpid());
        exit(42);  // Retorna um status específico para o pai
    }
    else {
        // Código do processo pai
        int status;
        printf("Processo pai aguardando pelo processo filho (PID: %d)...\n", pid);

        // Aguarda o término do processo filho específico
        pid_t child_pid = waitpid(pid, &status, 0);

        if (child_pid == -1) {
            perror("Erro ao usar waitpid");
            exit(EXIT_FAILURE);
        }

        // Verifica como o processo filho terminou
        if (WIFEXITED(status)) {
            printf("Processo filho terminou normalmente com status %d.\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Processo filho foi terminado por um sinal %d.\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
            printf("Processo filho foi parado por um sinal %d.\n", WSTOPSIG(status));
        }
    }
    return 0;
}
*/
/*
int main()
{
    char cwd[1024];  // Buffer para armazenar o caminho

    // Obtém o diretório de trabalho atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
	{
        printf("Diretório de trabalho atual: %s\n", cwd);
    } else {
        perror("Erro ao obter o diretório de trabalho atual");
        exit(EXIT_FAILURE);
    }

    return 0;
}
*/
/*
int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Erro ao criar o processo filho");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Processo filho
        printf("Processo filho (PID: %d) executando...\n", getpid());
        sleep(2);  // Simula alguma carga de trabalho
        printf("Processo filho (PID: %d) finalizando...\n", getpid());
        exit(42);
    } else {
        // Processo pai
        int status;
        struct rusage usage;

        // Espera por qualquer processo filho
        pid_t child_pid = wait3(&status, 0, &usage);

        if (child_pid == -1) {
            perror("Erro ao usar wait3");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("Filho com PID %d terminou com status %d.\n", child_pid, WEXITSTATUS(status));
            printf("Uso de CPU do filho: %ld segundos e %ld microssegundos\n",
                   usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
            printf("Memória máxima usada pelo filho: %ld KB\n", usage.ru_maxrss);
        }
    }

    return 0;
}
*/
/*
int main() {
    pid_t pid1 = fork();

    if (pid1 == -1) {
        perror("Erro ao criar o primeiro processo filho");
        exit(EXIT_FAILURE);
    } else if (pid1 == 0) {
        // Primeiro processo filho
        printf("Primeiro processo filho (PID: %d) executando...\n", getpid());
        sleep(3);  // Simula trabalho
        printf("Primeiro processo filho (PID: %d) finalizando...\n", getpid());
        exit(1);
    }

    pid_t pid2 = fork();

    if (pid2 == -1) {
        perror("Erro ao criar o segundo processo filho");
        exit(EXIT_FAILURE);
    } else if (pid2 == 0) {
        // Segundo processo filho
        printf("Segundo processo filho (PID: %d) executando...\n", getpid());
        sleep(5);  // Simula trabalho
        printf("Segundo processo filho (PID: %d) finalizando...\n", getpid());
        exit(2);
    }

    // Processo pai
    int status;
    struct rusage usage;

    // Aguarda especificamente pelo segundo processo filho
    pid_t child_pid = wait4(pid2, &status, 0, &usage);

    if (child_pid == -1) {
        perror("Erro ao usar wait4");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
        printf("Segundo filho com PID %d terminou com status %d.\n", child_pid, WEXITSTATUS(status));
        printf("Uso de CPU do segundo filho: %ld segundos e %ld microssegundos\n",
               usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
        printf("Memória máxima usada pelo segundo filho: %ld KB\n", usage.ru_maxrss);
    }

    return 0;
}
*/
/*
int main()
{
    char cwd[1024];  // Buffer para armazenar o diretório atual

    // Obtém e exibe o diretório de trabalho atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretório de trabalho atual: %s\n", cwd);
    } else {
        perror("Erro ao obter o diretório de trabalho atual");
        exit(EXIT_FAILURE);
    }

    // Muda para o diretório /tmp
    if (chdir("/tmp") == 0) {
        printf("Mudança para o diretório /tmp foi bem-sucedida.\n");
    } else {
        perror("Erro ao mudar para o diretório /tmp");
        exit(EXIT_FAILURE);
    }

    // Confirma o novo diretório de trabalho
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Novo diretório de trabalho: %s\n", cwd);
    } else {
        perror("Erro ao obter o novo diretório de trabalho");
        exit(EXIT_FAILURE);
    }
	    // Obtém e exibe o diretório de trabalho atual
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Diretório de trabalho atual: %s\n", cwd);
    } else {
        perror("Erro ao obter o diretório de trabalho atual");
        exit(EXIT_FAILURE);
    }

    return 0;
}
*/
/*
int main() {
    struct stat fileInfo;

    // Usando stat
    if (stat("./btree_int.c", &fileInfo) == 0) {
        printf("Tamanho: %lld bytes\n", (long long)fileInfo.st_size);
    } else {
        perror("Erro ao chamar stat");
    }

    // Usando lstat
    if (lstat("./btree_int.c", &fileInfo) == 0) {
        printf("Tamanho do link simbólico: %lld bytes\n", (long long)fileInfo.st_size);
    } else {
        perror("Erro ao chamar lstat");
    }

    // Usando fstat
    int fd = open("./btree_int.c", O_RDONLY);
    if (fd != -1) {
        if (fstat(fd, &fileInfo) == 0) {
            printf("Tamanho usando fstat: %lld bytes\n", (long long)fileInfo.st_size);
        } else {
            perror("Erro ao chamar fstat");
        }
        close(fd);
    } else {
        perror("Erro ao abrir arquivo");
    }

    return 0;
}
*/
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
    if (isatty(STDIN_FILENO)) {
        printf("Entrada padrão é um terminal.\n");
    } else {
        printf("Entrada padrão não é um terminal.\n");
    }

    if (isatty(STDOUT_FILENO)) {
        printf("Saída padrão é um terminal.\n");
    } else {
        printf("Saída padrão não é um terminal.\n");
    }

    return 0;
}
*/
/*
int main() {
    char *tty;

    tty = ttyname(STDIN_FILENO);
    if (tty != NULL) {
        printf("Terminal associado à entrada padrão: %s\n", tty);
    } else {
        perror("Erro ao obter o nome do terminal para a entrada padrão");
    }

    tty = ttyname(STDOUT_FILENO);
    if (tty != NULL) {
        printf("Terminal associado à saída padrão: %s\n", tty);
    } else {
        perror("Erro ao obter o nome do terminal para a saída padrão");
    }

    return 0;
}
*/
/*
int main() {
    int slot;

    slot = ttyslot();
    if (slot > 0) {
        printf("Número da entrada no arquivo /etc/ttys: %d\n", slot);
    } else {
        perror("Erro ao obter o número da entrada no arquivo /etc/ttys");
    }

    return 0;
}
*/
/*
int main() {
    struct winsize w;

    // Obtém o tamanho da janela do terminal associado à saída padrão
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == -1) {
        perror("Erro ao obter o tamanho da janela do terminal");
        return 1;
    }

    printf("Linhas: %d\n", w.ws_row);
    printf("Colunas: %d\n", w.ws_col);

    return 0;
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
/*
int main() {
    struct termios tty;

    // Obtém os atributos atuais do terminal
    if (tcgetattr(STDIN_FILENO, &tty) != 0) {
        perror("Erro ao obter atributos do terminal");
        return 1;
    }

    // Desativa o modo canônico e o eco
    tty.c_lflag &= ~(ICANON | ECHO);

    // Define os novos atributos do terminal
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) != 0) {
        perror("Erro ao definir atributos do terminal");
        return 1;
    }

    printf("Modo canônico e eco desativados. Digite algo (Ctrl+D para sair):\n");

    // Lê e imprime caracteres até o usuário pressionar Ctrl+D
    char c;
    while (read(STDIN_FILENO, &c, 1) > 0) {
        printf("%c", c);
    }

    // Restaura os atributos originais do terminal
    tty.c_lflag |= (ICANON | ECHO);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &tty) != 0) {
        perror("Erro ao restaurar atributos do terminal");
        return 1;
    }

    printf("\nAtributos do terminal restaurados.\n");

    return 0;
}
*/
/*
int main() {
    char term_buffer[2048];
    char *term_type = getenv("TERM");

    if (term_type == NULL) {
        fprintf(stderr, "A variável de ambiente TERM não está definida.\n");
        return 1;
    }

    // Inicializa a entrada do terminal
    if (tgetent(term_buffer, term_type) != 1) {
        fprintf(stderr, "Erro ao inicializar a entrada do terminal.\n");
        return 1;
    }

    // Verifica se o terminal suporta cores
    if (tgetflag("co")) {
        printf("O terminal suporta cores.\n");
    } else {
        printf("O terminal não suporta cores.\n");
    }

    // Obtém o número de linhas e colunas do terminal
    int line = tgetnum("li");
    int cols = tgetnum("co");

    if (line == -1 || cols == -1) {
        fprintf(stderr, "Erro ao obter o número de linhas ou colunas do terminal.\n");
        return 1;
    }

    printf("Linhas: %d, Colunas: %d\n", line, cols);

    // Obtém a string de inicialização do terminal
    char *clear_scree = tgetstr("cl", NULL);
    if (clear_scree == NULL) {
        fprintf(stderr, "Erro ao obter a string de limpeza da tela.\n");
        return 1;
    }

    // Limpa a tela
    tputs(clear_scree, 1, putchar);

    // Move o cursor para uma posição específica
    char *move_cursor = tgetstr("cm", NULL);
    if (move_cursor == NULL) {
        fprintf(stderr, "Erro ao obter a string de movimentação do cursor.\n");
        return 1;
    }

    char *cursor_position = tgoto(move_cursor, 10, 5);
    tputs(cursor_position, 1, putchar);

    printf("Cursor movido para a posição (10, 5).\n");

    return 0;
}
*/
