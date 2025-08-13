/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plan_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:32:35 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/12 22:35:02 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_plan_checker(char **split)
{
	if (ft_coords_checker(split[1]))
		return (1);
	else if (ft_coords_checker(split[2]))
		return (1);
	else if (ft_coords_checker(split[3]))
		return (1);
	return (0);
}

int	ft_plan_parse(char **a, char **p, char **c, t_scene *sc)
{
	t_vec3	axis;
	t_vec3	point;
	t_vec3	color;
	int		error;

	error = 0;
	if (ft_coords_float_checker(a) || ft_color_checker(c)
		|| ft_coords_float_checker(p))
		error = 4;
	if (!error)
	{
		point = ft_vec3(ft_to_double(p[0]), ft_to_double(p[1]),
				ft_to_double(p[2]));
		axis = ft_vec3(ft_to_double(a[0]), ft_to_double(a[1]),
				ft_to_double(a[2]));
		color = ft_vec3(ft_to_double(c[0]), ft_to_double(c[1]),
				ft_to_double(c[2]));
		if (ft_length_checker(&axis))
			error = 8;
		ft_insert_object(ft_create_plane(axis, point, color), sc);
	}
	free(p);
	free(a);
	free(c);
	return (error);
}

int	ft_init_plan(char **split, t_scene *scene)
{
	char	**axis;
	char	**point;
	char	**color;
	int		error;

	if (ft_len(split) != 4 || ft_plan_checker(split))
		return (2);
	axis = ft_fast_split(ft_to_space(split[2]));
	point = ft_fast_split(ft_to_space(split[1]));
	color = ft_fast_split(ft_to_space(split[3]));
	if (axis == NULL || point == NULL
		|| color == NULL
		|| ft_len(axis) != 3
		|| ft_len(point) != 3
		|| ft_len(color) != 3)
	{
		error = 2;
		if (axis == NULL || point == NULL || color == NULL)
			error = -1;
		free(axis);
		free(color);
		free(point);
		return (error);
	}
	return (ft_plan_parse(axis, point, color, scene));
}
