/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parsing_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:13 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:04:04 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	*space_gestion_before_text(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (line + i);
}

bool	is_config_line(char *line)
{
	line = space_gestion_before_text(line);
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

bool	is_color_config_line(char *line)
{
	return (ft_strncmp(line, "F", 1) == 0
		|| ft_strncmp(line, "C", 1) == 0);
}

/*
VERIFIE QU UN CHEMIN DE TEXTURE EST VALIDE
IL NE DOIT PAS ETRE NULL
IL DOIT AVOIR AU MOINS 5 CHARS
IL DOIT SE TERMINER PAR .XPM
IL DOIT Y AVOIR UN NOM DE FICHIER AVANT L'EXTENSION
TER DOSYA ADI + 4 KARAKTER .XPM
*/
int	valid_texture_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
	{
		printf("%sError: Invalid texture path: %s\n", ERROR, path);
		return (ERR);
	}
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0)
	{
		printf("%sError: Texture path must be an .xpm file: %s\n", ERROR, path);
		return (ERR);
	}
	if (len == 4 || path[len - 5] == '/')
	{
		printf("%sError: There is no filename before .xpm: %s\n", ERROR, path);
		return (ERR);
	}
	return (SUCCESS);
}

int	missing_texture_line(t_direction *flag)
{
	t_check	checks[6];
	int		i;
	int		error;

	error = 0;
	i = 0;
	checks[0] = (t_check){&flag->no, NO_NORTH_TEXT};
	checks[1] = (t_check){&flag->so, NO_SOUTH_TEXT};
	checks[2] = (t_check){&flag->we, NO_WEST_TEXT};
	checks[3] = (t_check){&flag->ea, NO_EAST_TEXT};
	checks[4] = (t_check){&flag->f, NO_FLOOR_TEXT};
	checks[5] = (t_check){&flag->c, NO_CEILING_TEXT};
	while (i < 6)
	{
		if (*checks[i].flag != 1)
		{
			error++;
			printf("%s%s", ERROR, checks[i].message);
		}
		i++;
	}
	return (error);
}
