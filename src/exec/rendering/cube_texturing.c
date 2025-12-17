/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_texturing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:22:19 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/16 18:22:20 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_texture(t_data *data, t_raycast *rc, t_draw *draw)
{
	select_texture_wrapper(data, rc, draw);
}
