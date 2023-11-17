/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 06:05:32 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/17 18:38:27 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialise_start(char *line, t_games_t *games)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 'P')
		{
			games->start_x = i;
			games->start_y = games->height - 1;
		}
	}
}

void	map_manager(char *line, t_games_t *games)
{
	char		**tmp_map;
	static int	count = 0;
	int			i;

	if (count == 0)
		games->lenght = ft_strlen(line);
	tmp_map = games->map;
	games->map = ft_calloc(count + 2, sizeof(char *));
	i = 0;
	while (i < count)
	{
		games->map[i] = tmp_map[i];
		i++;
	}
	games->map[count] = ft_strdup(line);
	games->map[count++ + 1] = 0;
	games->height = count;
	initialise_start(line, games);
}

void	initialise(char **argv, t_games_t *games)
{
	char	*line;
	int		i;

	games->exit = 0;
	games->item = 0;
	games->spawn = 0;
	games->file_name = ft_strdup(argv[1]);
	while (1)
	{
		line = get_next_line(games->fd);
		if (line == NULL)
			break ;
		map_manager(line, games);
		i = -1;
		while (line[++i])
		{
			if (line[i] == 'C')
				games->item += 1;
			if (line[i] == 'E')
				games->exit += 1;
			if (line[i] == 'P')
				games->spawn += 1;
		}
	}
	free(line);
}

int	main(int argc, char **argv)
{
	t_games_t	games;
	char		*error;

	if (argc != 2)
		return (1);
	games.fd = open(argv[1], O_RDONLY);
	if (games.fd <= 0)
	{
		ft_printf("Error\nUnable to open file.\n");
		return (1);
	}
	initialise(argv, &games);
	error = check_error(&games);
	if (error)
	{
		free(games.map);
		ft_printf("Error\n%s\n", error);
		return (1);
	}
	start(&games);
	return (0);
}
