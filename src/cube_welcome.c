/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_welcome.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 11:40:27 by cczerwin          #+#    #+#             */
/*   Updated: 2025/11/01 11:40:28 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	cube_welcome(void)
{
	printf(B_WHITE"\n\tCheck algo.md and math.md!%s\n\n", END);
	if (WIDTH > MAX_WID || WIDTH < MIN_WID
		|| HEIGHT > MAX_HEI || HEIGHT < MIN_HEI)
	{
		printf(B_RED"Wrong screen resolution, please check [cube.h]\n");
		printf("\t(%d*%d to %d*%d)%s\n\n"
			, MIN_WID, MIN_HEI, MAX_WID, MAX_HEI, END);
		exit(0);
	}
}
