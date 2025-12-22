/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:30:59 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 16:50:29 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_texture_path(t_map *map, char **split);

int	check_double_id(t_direction *flag, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0 && ++flag->no > 1)
		return (-1);
	if (ft_strncmp(id, "SO", 2) == 0 && ++flag->so > 1)
		return (-1);
	if (ft_strncmp(id, "WE", 2) == 0 && ++flag->we > 1)
		return (-1);
	if (ft_strncmp(id, "EA", 2) == 0 && ++flag->ea > 1)
		return (-1);
	if (ft_strncmp(id, "F", 1) == 0 && ++flag->f > 1)
		return (-1);
	if (ft_strncmp(id, "C", 1) == 0 && ++flag->c > 1)
		return (-1);
	return (0);
}

/*
for exemple for this texture : 
F 220,  100,  0
C 225,  30,   0
i do split pour the spaces, this breaks the tgb into multiple parts
--> split[0] = "F", split[1] = "220," split[2] = "" but my code 
was only using split[1] so it sent only "220," which ends with a comma
as this was an error, rgb line wasnt being splitted correctly.
it should have been ---> ID + MULTIPLE VALUES (sometimes broken due to spaces)
to rebuild rgb line correctly i do concatenation of 
split[1] + split[2] + split[3] etc
*/
static char	*join_rgb_parts_after_split(char **split)
{
	char	*res;
	char	*temp;
	int		i;

	i = 1;
	res = ft_strdup("");
	if (!res)
		return (printf("%sJoin rgb parts after split failed.\n", ERROR), NULL);
	while (split[i])
	{
		temp = ft_strjoin(res, split[i]);
		free(res);
		res = temp;
		i++;
	}
	return (res);
}

int	parse_texture_line(char *line, t_map *map)
{
	char	**splt;
	int		status;
	char	*res;

	splt = ft_split(line, ' ');
	if (!splt || !splt[0] || !splt[1])
		return (free_dbl_arr(splt), 0);
	status = check_double_id(&map->flags, splt[0]);
	if (status == -1)
		return (free_dbl_arr(splt), status);
	res = join_rgb_parts_after_split(splt);
	if (!res)
		return (free_dbl_arr(splt), 0);
	if (!is_color_config_line(splt[0]) && parse_texture_path(map, splt))
		return (free (res), free_dbl_arr(splt), 1);
	else if (ft_strncmp(splt[0], "F", 1) == 0
		&& parse_colors(res, map->floor) == 0)
		return (free(res), free_dbl_arr(splt), 0);
	else if (ft_strncmp(splt[0], "C", 1) == 0
		&& parse_colors(res, map->ceiling) == 0)
		return (free(res), free_dbl_arr(splt), 0);
	else
		return (free(res), free_dbl_arr(splt), -1);
	return (free(res), free_dbl_arr(splt), 0);
}

/*
ASSOCIE UN CHEMIN DE TEXTURE A LA DIRECTION CORRESPONDANTE
DANS LE MAP
ELL SUPPRIME LE RETOUR A LA LIGNE, VERIFIE QUE LE CHEMIN
EST VALIDE
PUIS COPIE LA CHAINE DANS LE BON EMPLACEMENT (NO SO WE EA)
*/

static int	parse_texture_path(t_map *map, char **split)
{
	remove_newline(split[1]);
	if (valid_texture_path(split[1]) == ERR)
		return (free_config(map), 0);
	if (ft_strncmp(split[0], "NO", 2) == 0)
		map->path[N] = ft_strdup(split[1]);
	else if (ft_strncmp(split[0], "SO", 2) == 0)
		map->path[S] = ft_strdup(split[1]);
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		map->path[W] = ft_strdup(split[1]);
	else if (ft_strncmp(split[0], "EA", 2) == 0)
		map->path[E] = ft_strdup(split[1]);
	else
		return (0);
	return (1);
}
