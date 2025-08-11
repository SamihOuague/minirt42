/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:30:55 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:35:03 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_cylinder_checker(char **split)
{
	if (ft_coords_checker(split[1]))
		return (1);
	else if (ft_coords_checker(split[2]))
		return (1);
	else if (ft_float_checker(split[3]))
		return (1);
	else if (ft_float_checker(split[4]))
		return (1);
	else if (ft_coords_checker(split[5]))
		return (1);
	return (0);
}

int	ft_cylinder_parse(char **b, char **a, char **s, char **c, t_scene *sc)
{
	t_vec3	base;
	t_vec3	axis;
	t_vec3	color;
	double	size[2];
	int		error;

	error = 0;
	if (ft_coords_float_checker(b)
		|| ft_color_checker(c)
		|| ft_coords_float_checker(a))
		error = 4;
	if (!error)
	{
		base = ft_vec3(ft_to_double(b[0]),
				ft_to_double(b[1]),
				ft_to_double(b[2]));
		axis = ft_vec3(ft_to_double(a[0]),
				ft_to_double(a[1]),
				ft_to_double(a[2]));
		color = ft_vec3(ft_to_double(c[0]),
				ft_to_double(c[1]),
				ft_to_double(c[2]));
		size[0] = ft_to_double(s[0]);
		size[1] = ft_to_double(s[1]);
		if (size[0] < 0 || size[1] < 0 || ft_length_checker(axis))
			error = 8;
		ft_insert_object(ft_create_cylinder(base, axis, size, color), sc);
	}
	free(b);
	free(a);
	free(c);
	return (error);
}

//t_vec3 base, t_vec3 axis, double size[2], t_vec3 color
int	ft_init_cylinder(char **split, t_scene *scene)
{
	char	**base;
	char	**axis;
	char	**color;
	char	*size[2];
	int		error;

	if (ft_len(split) != 6 || ft_cylinder_checker(split))
		return (2);
	base = ft_fast_split(ft_to_space(split[1]));
	axis = ft_fast_split(ft_to_space(split[2]));
	color = ft_fast_split(ft_to_space(split[5]));
	size[0] = split[3];
	size[1] = split[4];
	if (base == NULL
		|| axis == NULL
		|| color == NULL
		|| ft_len(base) != 3
		|| ft_len(axis) != 3
		|| ft_len(color) != 3)
	{
		error = 2;
		if (base == NULL || color == NULL || axis == NULL)
			error = -1;
		free(base);
		free(color);
		free(axis);
		return (error);
	}
	return (ft_cylinder_parse(base, axis, size, color, scene));
}
