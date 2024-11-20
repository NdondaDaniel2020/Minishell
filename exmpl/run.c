#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *analize_env(const char *env)
{
    int i, count_equals = 0;
    int len = strlen(env);
    char *new_env;

    // Contar o número de sinais de igual na string
    for (i = 0; i < len; i++)
    {
        if (env[i] == '=')
        {
            count_equals++;
        }
    }
    // Se houver mais de um sinal de igual ou terminar com igual, modificar a string
    if (count_equals > 1 || env[len - 1] == '=')
    {
        new_env = (char *)malloc(len + 3); // 2 para aspas e 1 para o terminador nulo
        if (!new_env)
        {
            return NULL; // Falha na alocação de memória
        }
        for (i = 0; env[i] != '='; i++)
        {
            new_env[i] = env[i];
        }
        new_env[i] = env[i];
        i++;
        new_env[i] = '"';
        i++;
        strcpy(new_env + i, env + i - 1);
        new_env[len + 1] = '"';
        new_env[len + 2] = '\0';

        return new_env;
    }
    return strdup(env);
}

int main()
{
    char *result;

    result = analize_env("ASDF=ASD");
    printf("%s\n", result);
    free(result);

    result = analize_env("ASDF==ASD");
    printf("%s\n", result);
    free(result);

    result = analize_env("ASDF========ASD");
    printf("%s\n", result);
    free(result);

    result = analize_env("ASDF=");
    printf("%s\n", result);
    free(result);

    return 0;
}
