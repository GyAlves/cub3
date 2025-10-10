int	ft_mapcontent(t_map *map)
{
	int		i;
	int		j;
	int		z;
	char	*possib_char;

	i = 0;
	j = 0;
	possib_char = "01NSEW";
	while (map->grid[i][j] != '\0' && z <= 5)
	{
		if (map->grid[i][j] != possib_char[z])
			z++;
		else
		{
			i++;
			z = 0;
		}
		if (z > 5 && map->grid[i][j] != '\0')
			return (0);
		else
			j++;
	}
	return (1);
}