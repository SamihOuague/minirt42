/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:28:35 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:33:30 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_sphere_checker(char **split)
{
	if (ft_coords_checker(split[1]))
		return (1);
	else if (ft_float_checker(split[2]))
		return (1);
	else if (ft_coords_checker(split[3]))
		return (1);
	return (0);
}

int	ft_sphere_parse(char **origin, char **color, char *radius, t_scene *scene)
{
	t_vec3	o;
	t_vec3	c;
	double	r;	
	int		error;

	error = 0;
	if (ft_coords_float_checker(origin)
		|| ft_color_checker(color))
		error = 4;
	if (!error)
	{
		r = ft_to_double(radius);
		o = ft_vec3(ft_to_double(origin[0]),
				ft_to_double(origin[1]),
				ft_to_double(origin[2]));
		c = ft_vec3(ft_atoi(color[0]),
				ft_atoi(color[1]),
				ft_atoi(color[2]));
		if (r < 0)
			error = 8;
		ft_insert_object(ft_create_sphere(o, r, c), scene);
	}
	free(origin);
	free(color);
	return (error);
}

int	ft_init_sphere(char **split, t_scene *scene)
{
	char	**origin;
	char	**color;
	char	*radius;
	int		error;

	if (ft_len(split) != 4 || ft_sphere_checker(split))
		return (2);
	origin = ft_fast_split(ft_to_space(split[1]));
	color = ft_fast_split(ft_to_space(split[3]));
	radius = split[2];
	if (origin == NULL
		|| color == NULL
		|| ft_len(origin) != 3
		|| ft_len(color) != 3)
	{
		error = 3;
		if (origin == NULL || color == NULL)
			error = -1;
		free(origin);
		free(color);
		return (error);
	}
	return (ft_sphere_parse(origin, color, radius, scene));
}
