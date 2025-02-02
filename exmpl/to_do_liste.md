o executar o comando
ex.:mkdir "TEST de algo le deve tirar as aspas ao criar o comando"

algo mis estranha que vi

algem fora do pico da montanha nao consegue ver a imensidao da paizagem do onhecimento.

ve algo muiti muito muito estranho

de algo que vc tem medo

de algo que vc tem medo

change_environment_variables_question_mark(126, data);

make re && make clean && clear && ./minishell
git clone --branch builtins --single-branch git@github.com:NdondaDaniel2020/Minishell.git




3 - cria uma funcao que recebe duas matrizes $A ou "ls -l"
$A ou "ls -l"
cria uma nova matriz
se o valor $A tiver espaco como "ls -l" -> "ls" -ls



S2020@gmailcoM


ab  cdef  gh

while (matrix[i1])
{
	if (ft_strchr(matrix[i1], '$'))
	{
		int	index;
		int start;

		index = 0;
		start = 0;
		break_point = 0;
		while (break_point != -1)
		{
			break_point = get_the_string_break_position(index, matrix[i1], matrix_exp[i1], data);
			if (index == 0 && break_point == -1)
			{
				new_matrix[i2++] = ft_strdup(matrix_exp[i1++]);
				break ;
			}
			else
			{
				while (matrix_exp[i1][start] == ' ')
					start++;
				if (break_point == -1)
				{
					new_matrix[i2++] = substring(matrix_exp[i1++], start, ft_strlen(matrix_exp[i1]));
					break ;
				}
				else
				{
					new_matrix[i2++] = substring(matrix_exp[i1], start, break_point);
					start = break_point;
				}
			}
			index++;
		}
	}
	else
		new_matrix[i2++] = ft_strdup(matrix_exp[i1++]);
}

typedef struct s_split_env
{
	int		i1;
	int		i2;
	int		len;
	int		index;
	int		break_point;
	char	**new_matrix;
}			t_split_env;