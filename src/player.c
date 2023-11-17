/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:42:31 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/15 23:04:17 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	collect_coin(t_games_t *games, int p_y, int p_x)
{
	int	i;

	if (!(games->map[p_y][p_x] == 'C'))
		return ;
	i = -1;
	while (++i < (int)games->img->img_coin->count)
	{
		if (games->img->img_coin->instances[i].y / 32 != p_y)
			continue ;
		if (games->img->img_coin->instances[i].x / 32 != p_x)
			continue ;
		if (!(games->img->img_coin->instances[i].enabled))
			continue ;
		games->img->img_coin->instances[i].enabled = false;
		games->item -= 1;
		if (games->item <= 0)
			games->player->has_exit = 1;
	}
}

void	up(t_games_t *games)
{
	int	p_x;
	int	p_y;

	p_x = games->player->x;
	p_y = games->player->y;
	if (games->map[p_y - 1][p_x] == '1')
		return ;
	if (games->map[p_y - 1][p_x] == 'E' && games->player->has_exit == 0)
		return ;
	games->img->img_player->instances[0].y -= 32;
	games->player->mouv += 1;
	games->player->y -= 1;
	ft_printf("%i\n", games->player->mouv);
	collect_coin(games, games->player->y, p_x);
	check_exit(games, games->player->y, p_x);
}

void	down(t_games_t *games)
{
	int	p_x;
	int	p_y;

	p_x = games->player->x;
	p_y = games->player->y;
	if (games->map[p_y + 1][p_x] == '1')
		return ;
	if (games->map[p_y + 1][p_x] == 'E' && games->player->has_exit == 0)
		return ;
	games->player->y += 1;
	games->player->mouv += 1;
	games->img->img_player->instances[0].y += 32;
	ft_printf("%i\n", games->player->mouv);
	collect_coin(games, games->player->y, p_x);
	check_exit(games, games->player->y, p_x);
}

void	left(t_games_t *games)
{
	int	p_x;
	int	p_y;

	p_x = games->player->x;
	p_y = games->player->y;
	if (games->map[p_y][p_x - 1] == '1')
		return ;
	if (games->map[p_y][p_x - 1] == 'E' && games->player->has_exit == 0)
		return ;
	games->player->x -= 1;
	games->player->mouv += 1;
	games->img->img_player->instances[0].x -= 32;
	ft_printf("%i\n", games->player->mouv);
	collect_coin(games, p_y, games->player->x);
	check_exit(games, p_y, games->player->x);
}

void	right(t_games_t *games)
{
	int	p_x;
	int	p_y;

	p_x = games->player->x;
	p_y = games->player->y;
	if (games->map[p_y][p_x + 1] == '1')
		return ;
	if (games->map[p_y][p_x + 1] == 'E' && games->player->has_exit == 0)
		return ;
	games->player->x += 1;
	games->player->mouv += 1;
	games->img->img_player->instances[0].x += 32;
	ft_printf("%i\n", games->player->mouv);
	collect_coin(games, p_y, games->player->x);
	check_exit(games, p_y, games->player->x);
}
