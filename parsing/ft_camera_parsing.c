/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:33:13 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:38:52 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_camera_checker(char **split)
{
	if (ft_coords_checker(split[1]))
		return (1);
	else if (ft_coords_checker(split[2]))
		return (1);
	else if (ft_float_checker(split[3]))
		return (1);
	return (0);
}

int	ft_set_camera(t_vec3 ori, t_vec3 dir, int fov, t_scene *scene)
{
	(*scene).camera.origin = ori;
	(*scene).camera.direction = dir;
	(*scene).camera.fov = fov;
	return (0);
}

int	ft_camera_parse(char **o, char **d, char *f, t_scene *s)
{
	t_vec3	origin;
	t_vec3	direction;
	int		fov;
	int		error;	

	error = 0;
	if (ft_coords_float_checker(o)
		|| ft_coords_float_checker(d)
		|| !ft_isnumeric(f))
		error = 4;
	if (!error)
	{
		origin = ft_vec3(ft_to_double(o[0]),
				ft_to_double(o[1]),
				ft_to_double(o[2]));
		direction = ft_vec3(ft_to_double(d[0]),
				ft_to_double(d[1]),
				ft_to_double(d[2]));
		fov = ft_atoi(f);
		if (fov < 0 || ft_length_checker(direction))
			error = 8;
		ft_set_camera(origin, direction, fov, s);
	}
	free(o);
	free(d);
	return (error);
}

int	ft_init_camera(char **split, t_scene *scene)
{
	char	**origin;
	char	**direction;
	char	*fov;
	int		error;

	if ((*scene).cla[0] > 0)
		return (5);
	(*scene).cla[0] = 1;
	if (ft_len(split) != 4 || ft_camera_checker(split))
		return (2);
	origin = ft_fast_split(ft_to_space(split[1]));
	direction = ft_fast_split(ft_to_space(split[2]));
	fov = split[3];
	if (origin == NULL
		|| direction == NULL
		|| ft_len(origin) != 3
		|| ft_len(direction) != 3)
	{
		error = 7;
		if (origin == NULL || direction == NULL)
			error = -1;
		free(origin);
		free(direction);
		return (error);
	}
	return (ft_camera_parse(origin, direction, fov, scene));
}
