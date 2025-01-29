/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cramos-c <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:04:26 by cramos-c          #+#    #+#             */
/*   Updated: 2024/12/09 12:04:37 by cramos-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "run.h"
#include <stdbool.h>
#include <stdio.h>

int main()
{
    const char *dirPath = "test";
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
