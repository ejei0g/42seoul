/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:46:13 by jaeylee           #+#    #+#             */
/*   Updated: 2020/10/15 20:34:40 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_cub3d.h"

int		animated_sprite(t_game *game)
{
	int	i;

	i = 0;
	while (i < NUM_SPRITE)
	{
		if (game->sprite[i].texture <= 9 && game->sprite[i].texture > 5)
			game->sprite[i].texture--;
		if (game->sprite[i].texture == 5)
			game->sprite[i].texture = 9;
		i++;
	}
	return (1);
}
