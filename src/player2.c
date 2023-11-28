/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aallou-v <aallou-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 00:42:31 by aallou-v          #+#    #+#             */
/*   Updated: 2023/11/20 14:25:54 by aallou-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_exit(t_games_t *games, int p_y, int p_x)
{
	if (games->map[p_y][p_x] != 'E')
		return ;
	ft_printf("Vous avez fini la carte %s en %i coup(s).\n",
		games->file_name, games->player->mouv);
	mlx_close_window(games->mlx);
}
