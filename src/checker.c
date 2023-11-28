/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 06:05:32 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/22 16:14:29 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_char(t_games_t *games)
{
	int	i;

	i = 0;
	while (games->map[i])
	{
		if (!ft_isonly(games->map[i], "ECP01\n"))
			return (0);
		i++;
	}
	return (1);
}

static int	check_is_close(t_games_t *games)
{
	int	i;

	i = 0;
	while (games->map[i])
	{
		if (games->map[i][0] != '1'
		|| games->map[i][ft_strlen(games->map[i]) - 2] != '1')
			return (0);
		i++;
	}
	if (!ft_isonly(games->map[i -1], "1\n") || !ft_isonly(games->map[0], "1\n"))
		return (0);
	return (1);
}

static int	check_is_rectangle(t_games_t *games)
{
	int	i;

	i = 0;
	while (games->map[i])
	{
		if (!games->map[i] || !games->map[i + 1])
			break ;
		if (ft_strlen(games->map[i]) != ft_strlen(games->map[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

char	*check_error(t_games_t *games)
{
	if (ft_strchr(games->file_name, '.') == NULL
		|| ft_strncmp(ft_strchr(games->file_name, '.'), ".ber", 4) != 0)
		return ("The file is not a .ber");
	if (games->exit != 1)
		return ("The number of outputs must be 1");
	if (games->spawn != 1)
		return ("The number of spawn points must be 1");
	if (games->item <= 0)
		return ("Number of items must be equal to or greater than 1");
	if (!check_is_rectangle(games))
		return ("The map must be a rectangle");
	if (!check_is_close(games))
		return ("The map must be close");
	if (!check_char(games))
		return ("The map must contain only : 1 / P / C / E / 0");
	initialise_map_checker(games);
	if (!check_is_possible(games, games->start_y, games->start_x))
	{
		free_checker(games);
		return ("The map must be possible");
	}
	return (NULL);
}
