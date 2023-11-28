/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 19:29:59 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/22 16:14:13 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../minilibx/mlx42.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct s_player
{
	int	x;
	int	y;
	int	mouv;
	int	has_exit;
}		t_player;

typedef struct s_texture
{
	mlx_texture_t	*player;
	mlx_image_t		*img_player;
	mlx_texture_t	*coin;
	mlx_image_t		*img_coin;
	mlx_texture_t	*ground;
	mlx_image_t		*img_ground;
	mlx_texture_t	*wall;
	mlx_image_t		*img_wall;
	mlx_texture_t	*exit;
	mlx_image_t		*img_exit;
}		t_texture;

typedef struct s_check
{
	int	item;
	int	exit;
	int	**checked;
}				t_check;

typedef struct games_s
{
	int			exit;
	int			item;
	int			spawn;
	int			fd;
	char		*file_name;
	int			height;
	int			lenght;
	char		**map;
	int			start_x;
	int			start_y;
	mlx_t		*mlx;
	t_texture	*img;
	t_player	*player;
	t_check		*checker;
}				t_games_t;

char	*check_error(t_games_t *games);
void	start(t_games_t *games);
void	up(t_games_t *games);
void	down(t_games_t *games);
void	right(t_games_t *games);
void	left(t_games_t *games);
void	check_exit(t_games_t *games, int p_y, int p_x);
void	exit_games(t_games_t *games);
int		check_is_possible(t_games_t *games, int y, int x);
void	initialise_map_checker(t_games_t *games);
void	free_checker(t_games_t *games);

#endif
