/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 16:01:17 by marvin            #+#    #+#             */
/*   Updated: 2025/02/28 16:01:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

void	left(t_game *game)
{
	int	new_x;

	new_x = game->vars.player_x - 1;
	if (game->map.map[game->vars.player_y][new_x] != '1')
	{
		game->vars.player_x = new_x;
		game->img_player = game->img_player_left;
	}
}

void	right(t_game *game) 
{
	int	new_x;

	new_x = game->vars.player_x + 1;
	if (game->map.map[game->vars.player_y][new_x] != '1')
	{
		game->vars.player_x = new_x;
		game->img_player = game->img_player_right;
	}
}
