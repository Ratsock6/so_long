/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_is_possible.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 20:46:55 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/22 16:20:18 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_checker(t_games_t *games)
{
	int	i;

	i = -1;
	while (++i < games->height)
		free(games->checker->checked[i]);
	free(games->checker->checked);
	free(games->checker);
}

void	initialise_map_checker(t_games_t *games)
{
	int	i;
	int	j;

	games->checker = malloc(sizeof(t_check));
	games->checker->checked = ft_calloc(games->height, sizeof(int *));
	games->checker->item = 0;
	games->checker->exit = 0;
	i = -1;
	while (++i < games->height)
		games->checker->checked[i] = ft_calloc(games->lenght - 1, sizeof(int));
	i = -1;
	while (++i < games->height)
	{
		j = -1;
		while (++j < games->lenght - 1)
			games->checker->checked[i][j] = 0;
	}
}

int	is_checked(t_games_t *games, int y, int x)
{
	return (games->checker->checked[y][x] == 1);
}

void	count_element(t_games_t *games, int y, int x)
{
	if (games->map[y][x] == 'C')
		games->checker->item += 1;
	if (games->map[y][x] == 'E')
		games->checker->exit += 1;
	games->checker->checked[y][x] = 1;
}

int	check_is_possible(t_games_t *games, int y, int x)
{
	int	result[4];

	result[0] = 0;
	result[1] = 0;
	result[2] = 0;
	result[3] = 0;
	count_element(games, y, x);
	if (games->checker->exit >= 1 && games->checker->item == games->item)
		return (1);
	if (x < 0 || x >= games->lenght || y < 0
		|| y >= games->height || games->map[y][x] == '1')
		return (0);
	if (games->map[y][x + 1] != '1' && !is_checked(games, y, x + 1))
		result[0] = check_is_possible(games, y, x + 1);
	if (games->map[y][x - 1] != '1' && !is_checked(games, y, x - 1))
		result[1] = check_is_possible(games, y, x - 1);
	if (games->map[y + 1][x] != '1' && !is_checked(games, y + 1, x))
		result[2] = check_is_possible(games, y + 1, x);
	if (games->map[y - 1][x] != '1' && !is_checked(games, y - 1, x))
		result[3] = check_is_possible(games, y - 1, x);
	return (result[0] || result[1] || result[2] || result[3]);
}
