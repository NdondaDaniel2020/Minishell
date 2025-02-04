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

/* usa o tipo index para fazer o ++ e add no index*/

#include "run.h"

static void	init_split(t_split *split, char *str, char chr)
{
    split->len = 0;
    split->in_quotes = 0;
    split->substr_count = 1;
    split->start = str;
    split->end = str;
    while (*split->end)
    {
        if (*split->end == '"' || *split->end == '\'')
            split->in_quotes = !split->in_quotes;
        else if (*split->end == chr && !split->in_quotes)
            split->substr_count++;
        split->end++;
    }
    split->result = (char **)malloc((split->substr_count + 1) * sizeof(char *));
    split->end = str;
}

static void	split_substring(int *i, t_split *split, char chr)
{
    split->result[*i] = strndup(split->start, split->end - split->start);
    (*i)++;
    while (*split->end == chr)
        split->end++;
    split->start = split->end;
}

char **split_3(char *str, char chr)
{
    int			i;
    t_split		split;

    i = 0;
    init_split(&split, str, chr);
    while (*split.end)
    {
        if (*split.end == '"' || *split.end == '\'')
            split.in_quotes = !split.in_quotes;
        else if (*split.end == chr && !split.in_quotes)
        {
            split_substring(&i, &split, chr);
            continue ;
        }
        split.end++;
    }
    split.result[i] = strndup(split.start, split.end - split.start);
    split.result[split.substr_count] = NULL;
    return (split.result);
}

int main(void)
{
    char *str = "export 'ls -l' 'continer' ''teste de string'' \"\"\"teste de string\"\"\"";
    char **result = split_3(str, ' ');
    int i = 0;
    while (result[i])
    {
        printf("[%s]\n", result[i]);
        i++;
    }
    return (0);
}