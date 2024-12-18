/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmatondo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:05:31 by nmatondo          #+#    #+#             */
/*   Updated: 2024/11/06 10:05:31 by nmatondo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_data(t_data *data, char *command)
{
	int		i;
	char	**spliting;

	i = 0;
	data->command = command;
	spliting = split_2(command, '|');
	while (spliting[i])
	{
		ft_lstnew_addfront(&data->list,
			ft_lstnew_new(split_2(spliting[i], ' ')));
		free(spliting[i]);
		i++;
	}
	free(spliting);
}

void	execute_command(int i, t_new_list *aux, t_data *data)
{
	if (!ft_strncmp(aux->content[i], "exit", ft_strlen(aux->content[i])))
		exit_(aux, data);
	else if (!ft_strncmp(aux->content[i], "pwd", ft_strlen (aux->content[i])))
		pwd(aux, data);
	else if (!ft_strncmp(aux->content[i], "cd", ft_strlen(aux->content[i])))
		cd(aux, data);
	else if (!ft_strncmp(aux->content[i], "echo", ft_strlen(aux->content[i])))
		echo(aux, data);
	else if (!ft_strncmp(aux->content[i], "env", ft_strlen(aux->content[i])))
		env(aux, data);
	else if (!ft_strncmp(aux->content[i], "export", ft_strlen(aux->content[i])))
		export(aux, data);
	else if (!ft_strncmp(aux->content[i], "unset", ft_strlen(aux->content[i])))
		unset(data);
	else
		other_command(i, aux, data);
}

void	redirection(int i, t_new_list *aux, t_data *data)
{
	int		it;
	int		len;
	char	**new_content;

	(void)i;
	new_content = reset_the_array_for_redirection(aux->content);
	if (new_content)
	{
		ft_lstnew_addafter_pos(&data->list, data->list, ft_lstnew_new(new_content));
		return ;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	
	len = len_matrix(aux->content);
	if	(!valid_string_condition_for_redirection(aux->content[len - 2]))
		ajust_position(&aux->content);
	
	//////////////////////////////////////////////////////////////////////////////////////

	if ((valid_string_condition_for_redirection(aux->content[len - 1]))
		|| ((ft_strlen(aux->content[len - 1]) == 0) && valid_string_condition_for_redirection(aux->content[len - 2])))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return ;
	}

	
	//////////////////////////////////////////////////////////////////////////////////////
	
	it = 0;
	while (aux->content[it])
	{	
		if (valid_string_condition_for_redirection(aux->content[it]) && is_directory_valid(aux->content[it + 1]))
		{
			ft_putstr_fd(aux->content[it + 1], 2);
			ft_putstr_fd(": Is a directory\n", 2);
			return ;
		}
		it++;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////

	if ((is_directory_valid(aux->content[len - 1]))
		|| ((ft_strlen(aux->content[len - 1]) == 0) && is_directory_valid(aux->content[len - 2])))
	{
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
		return ;
	}
	
	//////////////////////////////////////////////////////////////////////////////////////
	it = 0;
	while (aux->content[it])  // 
	{
		ft_printf("[%s]", aux->content[it]);
		it++;
	}

	ft_printf("\n");

	//2 - E depois verifique se a sintaxe do redirecionamento e valida
		// v/ verificar se alguma finformacao depois do redirecionamento e um diretorio, [echo "texto" > /HOME]
		// v/ redirecionamento incompleto [echo "texto" >] [echo > file >]
		/// nao aceitar diferente de >, <, >>, <<
		/// nao aceitar um sinal ao lado do ourto /// nao aceitar 

	//3 - Tratamento
		/// se tiver espancoem algum llugar do nome do arquivo 
		/// se tiver espancoem algum llugar do nome do arquivo
		/// se tiver ""' file '"" -> file 
		/// ->> retire apenas as chavetar que podem ser ' ou " e o resto vai no file
		/// not / & ! $ ( ) > < >> <<

	// ...DEPOIS DE CADA (>, <, >>, <<) REDIRECIONAMENTO FUNCIONAR SOZINHO 
	// ESTUDAR OS REDIRECIONAMENTO COMHINADO 
}

void	master(char *command, t_data *data)
{
	int			i;
	t_new_list	*aux;

	if (count_chr('\'', command) % 2 != 0 || count_chr('"', command) % 2 != 0)
	{
		ft_putstr("unclosed quotes\n", 2);
		return ;
	}
	insert_data(data, command);
	aux = data->list;
	while (aux)
	{
		i = 0;
		if (ft_strlen(aux->content[i]) == 0)
			i++;
		if (is_redirection(data->command))
			redirection(i, aux, data);
		else
			execute_command(i, aux, data);
		aux = aux->next;
	}
	free_all_data(data);
}

int	main(void)
{
	t_data	data;
	char	*input;

	init_data(&data);
	data.envp = get_all_environment();
	data.path = ft_split(get_env("PATH", &data), ':');
	while (1)
	{
		input = readline("TeamWork> ");
		if (input[0] != '\0')
		{
			add_history(input);
			master(input, &data);
			free(input);
		}
	}
	return (0);
}
