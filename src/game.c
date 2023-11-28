/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 23:53:44 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/22 16:20:44 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	exit_games(t_games_t *games)
{
	int	i;

	mlx_delete_image(games->mlx, games->img->img_coin);
	mlx_delete_texture(games->img->coin);
	mlx_delete_image(games->mlx, games->img->img_exit);
	mlx_delete_texture(games->img->exit);
	mlx_delete_image(games->mlx, games->img->img_ground);
	mlx_delete_texture(games->img->ground);
	mlx_delete_image(games->mlx, games->img->img_player);
	mlx_delete_texture(games->img->player);
	mlx_delete_image(games->mlx, games->img->img_wall);
	mlx_delete_texture(games->img->wall);
	mlx_terminate(games->mlx);
	free(games->file_name);
	i = -1;
	while (++i < games->height)
		free(games->map[i]);
	free(games->map);
	free(games->img);
	free(games->player);
	free_checker(games);
}

void	init_texture(t_games_t *games)
{
	games->img = malloc(sizeof(t_texture));
	games->player = malloc(sizeof(t_player));
	games->img->coin = mlx_load_png("texture/coin.png");
	games->img->img_coin = mlx_texture_to_image(games->mlx,
			games->img->coin);
	games->img->exit = mlx_load_png("texture/exit.png");
	games->img->img_exit = mlx_texture_to_image(games->mlx,
			games->img->exit);
	games->img->player = mlx_load_png("texture/player.png");
	games->img->img_player = mlx_texture_to_image(games->mlx,
			games->img->player);
	games->img->ground = mlx_load_png("texture/ground.png");
	games->img->img_ground = mlx_texture_to_image(games->mlx,
			games->img->ground);
	games->img->wall = mlx_load_png("texture/wall.png");
	games->img->img_wall = mlx_texture_to_image(games->mlx,
			games->img->wall);
}

void	map_generator(void *param)
{
	int			x;
	int			y;
	t_games_t	*games;

	games = param;
	y = -1;
	while (++y < games->height)
	{
		x = -1;
		while (++x < games->lenght - 1)
		{
			mlx_image_to_window(games->mlx, games->img->img_ground,
				x * 32, y * 32);
			if (games->map[y][x] == '1')
				mlx_image_to_window(games->mlx, games->img->img_wall,
					x * 32, y * 32);
			if (games->map[y][x] == 'C')
				mlx_image_to_window(games->mlx, games->img->img_coin,
					x * 32, y * 32);
			if (games->map[y][x] == 'E')
				mlx_image_to_window(games->mlx, games->img->img_exit,
					x * 32, y * 32);
		}
	}
}

void	ft_hook(mlx_key_data_t keydata, void *param)
{
	t_games_t	*games;

	games = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(games->mlx);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		up(games);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		down(games);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		left(games);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		right(games);
}

void	start(t_games_t *games)
{
	games->mlx = mlx_init((games->lenght - 1) * 32,
			games->height * 32, games->file_name, true);
	if (!games->mlx)
		return ;
	init_texture(games);
	map_generator(games);
	mlx_image_to_window(games->mlx, games->img->img_player, 0, 0);
	games->img->img_player->instances[0].y = games->start_y * 32;
	games->img->img_player->instances[0].x = games->start_x * 32;
	games->player->x = games->start_x;
	games->player->y = games->start_y;
	games->player->mouv = 0;
	games->player->has_exit = 0;
	mlx_set_icon(games->mlx, games->img->player);
	mlx_key_hook(games->mlx, ft_hook, games);
	mlx_loop(games->mlx);
	exit_games(games);
}
