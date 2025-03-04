/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:01:25 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:01:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	down(t_game *game)
{
	int	new_y;

	new_y = game->vars.player_y + 1;
	if (game->map.map[new_y][game->vars.player_x] != '1')
	{
		game->vars.player_y = new_y;
		game->img_player = game->img_player_down;
	}
}

void	up(t_game *game)
{
	int	new_y;

	new_y = game->vars.player_y - 1;
	if (game->map.map[new_y][game->vars.player_x] != '1')
	{
		game->vars.player_y = new_y;
		game->img_player = game->img_player_up;
	}
}
