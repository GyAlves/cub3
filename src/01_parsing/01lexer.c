/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01lexer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jucoelho <juliacoelhobrandao@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 20:19:23 by jucoelho          #+#    #+#             */
/*   Updated: 2025/10/27 18:49:06 by jucoelho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_rgb_to_int(t_map *map, int *rgb, char color_type)
{
	if (color_type == 'F')
	{
		if (map->floor_color != -1)
		{
			printf("Error: Map with repeated floor color");
			return (0);
		}
		return ((map->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[3]), 1);
	}
	else if (color_type == 'C')
	{
		if (map->ceiling_color != -1)
		{
			printf("Error: Map with repeated ceiling color");
			return (0);
		}
		return ((map->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[3]), 1);
	}
	else if (rgb[0] < 0 || rgb[0] > 255 || rgb[1] < 0 || rgb[1] > 255 || rgb[3] < 0 || rgb[3] > 255)
		return (0);
	return (0);
}

int	ft_valid_colortoken(t_map *map, int i, char color_type)
{
	char	*str;
	char	**color;
	int		rgb[3];
	int		z;

	z = 0;
	str = ft_strtrim(map->grid[i] + 1, " ");
	if (!str)
		return (0);
	color = ft_split(str, ',');
	if (!color)
		return (free(str), 0);
	while (color[z])
		z++;
	if (z != 3)
		return (ft_free_map(color), free(str), 0);
	z = 0;
	while (z < 3)
	{
		rgb[z] = ft_atoi(color[z]);
		if (rgb[z] < 0 || rgb[z] > 255)
			return (ft_free_map(color), free(str), 0);
		z++;
	}
	ft_rgb_to_int(map, rgb, color_type);
	free(str);
	ft_free_map(color);
	return (1);
}

int	ft_valid_textoken(t_game *game, int i, int j, int tex_type)
{
	int		len;

	//ft_printf("valid token 1 j = %d game->grid[%d] = %s\n", j, i, game->map.grid[i]);
	while (game->map.grid[i][j] == ' ')
		j++;
	//ft_printf("valid token 2 j = %d game->grid[%d] = %s\n", j, i, game->map.grid[i]);
	len = game->map.width[i] - j;
	if (game->textures[tex_type].addr != NULL)
	{
		printf("Error: Map with repeated texture");
		return (0);
	}
	game->textures[tex_type].addr = ft_substr(game->map.grid[i], j, len);
	if (!game->textures[tex_type].addr)
		return (0);
	ft_printf("valid token =%s\n", game->textures[tex_type].addr);
	return (1);
}

int	ft_valid_token(t_game *game, int i, int j, char token_type)
{
	if (game->map.grid[i][j] == 'N' && game->map.grid[i][j + 1] == 'O')
		return (ft_valid_textoken(game, i, j + 2, 0));
	if (game->map.grid[i][j] == 'S' && game->map.grid[i][j + 1] == 'O')
		return (ft_valid_textoken(game, i, j + 2, 1));
	if (game->map.grid[i][j] == 'W' && game->map.grid[i][j + 1] == 'E')
		return (ft_valid_textoken(game, i, j + 2, 2));
	if (game->map.grid[i][j] == 'E' && game->map.grid[i][j + 1] == 'A')
		return (ft_valid_textoken(game, i, j + 2, 3));
	if (game->map.grid[i][j] == 'F')
		return (ft_valid_colortoken(&game->map, i, 'F'));
	if (game->map.grid[i][j] == 'C')
		return (ft_valid_colortoken(&game->map, i, 'C'));
	return (0);
}
int	ft_verifytexcolor(t_game *game)
{
	int	j;
	j = 0;
	while(j < 4)
	{
		if (game->textures[j].addr == NULL)
			return(ft_printf("Error: Map texture incomplete %d\n", j), 0);
		j++;
	}
	j = 0;
	if (game->map.ceiling_color == -1 || game->map.floor_color == -1)
		return(ft_printf("Error: Map color incomplete\n"), 0);
	return (1);
}

int	ft_process_line(t_game *game, int *i, int *j)
{
	int		z;
	char	*possib_char;

	z = 0;
	possib_char = "NSWEFC";
	//primeira parte, pular linhas vazias do início do mapa ou entre elementos
	while(*i < game->map.height && game->map.grid[*i][*j] == '\0')//pula linha vazia 
		(*i)++;
	while (*j < game->map.width[*i] && game->map.grid[*i][*j] == ' ')//linha não vazia pula um espaço
		(*j)++;//incrementa j
	if (*j >= game->map.width[*i])//se foi só linha vazia tem que dar erro
	{
		//ft_printf("i= %d, linha vazia tem que dar erro\n", *i);
		*i = game->map.height;
		return (ft_printf("Error: Unexpected content between elements; only empty lines are allowed.\n"), 0);
	}
	//segunda parte achar a primeira linha de textura ou cor
	while (possib_char[z] != '\0' && game->map.grid[*i][*j] != possib_char[z])//procura qual a tex/cor
		z++;
	if (game->map.grid[*i][*j] == possib_char[z])//achou uma tex/cor
	{
		if (ft_valid_token(game, *i, *j, possib_char[z]))//atribui a tex/cor
		{
			//ft_printf("free process line i = %d, j = %d, possib_char[z] = %c\n", *i, *j, possib_char[z]);
			
			(*i)++;//incrementa linha
			*j = 0;//reseta j
			return (0);//retorna lexar
		}
	}
	//já achou todas as texturas ou cores ou não tem todas (isso verifica depois 	ft_verifytexcolor)
	return (1);
}



int	ft_compact_map(t_game *game, int start)
{
	int	z;

	z = 0;
	while (z < start)
	{
		if (game->map.width[z] >= 0)
			free(game->map.grid[z]);
		z++;
	}
	z = 0;
	while (z + start < game->map.height)// start(é onde o mapa começa depois das tex e cores)
	// Z + START é menor altura do mapa 
	{
		game->map.grid[z] = game->map.grid[z + start]; //linha 0 agora é = a linha 0 + i (exemplo i = 8)
		game->map.width[z] = game->map.width[z + start];//largura da linha 0 agora é largura da linha 8 
		z++;//z = 1
		/*loop de novo
		z = 1,
		1 + 8 = 9 (9 é menor que a largura total ex 13)
		se sim, continua a busca e atrubuiçção*/
	}//z = 5 pq 5+ 8 = 13 ()
	/*while (z < game->map.height)
	{
		game->map.grid[z] = NULL;
		game->map.width[z] = -1;
		z++;
	}*/
	game->map.height -= start;
	return (1);
}

int	ft_lexer(t_game *game)
{
	int	i;
	int	j;
	int	z;

	i = 0;
	j = 0;
	z = game->map.height - 1;
	ft_printf("entrou no lexer i %d, j %d, z %d\n", i, j, z);
	while (game->map.grid[z][0] == '\0' && z > 0)
	{
		//ft_printf("entrou no lexer 1º while i %d, j %d, z %d\n", i, j, z);
		free(game->map.grid[z]);
		game->map.grid[z] = NULL;
		game->map.width[z] = -1;
		z--;
	}
	if (z == 0)
	{
		ft_printf("Error: empty map\n");
		return (0);
	}
	game->map.height = z + 1;
	ft_printf("map.height = %d\n", z + 1);
	while (i < game->map.height)
	{
		if(ft_process_line(game, &i, &j))// 0 entra de novo no while
		{//se retornou 1 entra aqui,
			if (game->map.grid[i][j] == '\0')//se a ultima linha tiver /0 
			{
				while (game->map.grid[i][j] == '\0')//incrementa i
					i++;
			}
			else//se não for /0 ou seja, achou uma linha com conteúdo
				return (ft_compact_map(game, i));//chama compact map para a primeira linha do mapa
		}
	}
	ft_printf("return 0\n");
	return (0);
}
