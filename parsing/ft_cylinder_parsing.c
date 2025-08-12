/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:30:55 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/12 03:31:12 by souaguen         ###   ########.fr       */
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

void	ft_cylinder_param_init(t_vec3 *base, t_vec3 *axis,
		t_vec3 *color, char **params[3])
{
	*base = ft_vec3(ft_to_double(params[0][0]),
			ft_to_double(params[0][1]),
			ft_to_double(params[0][2]));
	*axis = ft_vec3(ft_to_double(params[1][0]),
			ft_to_double(params[1][1]),
			ft_to_double(params[1][2]));
	*color = ft_vec3(ft_to_double(params[2][0]),
			ft_to_double(params[2][1]),
			ft_to_double(params[2][2]));
}

int	ft_cylinder_parse(char **params[3], char **s, t_scene *sc)
{
	t_vec3	base;
	t_vec3	axis;
	t_vec3	color;
	double	size[2];
	int		error;

	error = 0;
	if (ft_coords_float_checker(params[0])
		|| ft_color_checker(params[2])
		|| ft_coords_float_checker(params[1]))
		error = 4;
	if (!error)
	{
		ft_cylinder_param_init(&base, &axis, &color, params);
		size[0] = ft_to_double(s[0]);
		size[1] = ft_to_double(s[1]) / 2;
		if (size[0] < 0 || size[1] < 0 || ft_length_checker(axis))
			error = 8;
		ft_insert_object(ft_create_cylinder(base, axis, size, color), sc);
	}
	free(params[0]);
	free(params[1]);
	free(params[2]);
	return (error);
}

int	ft_init_cylinder(char **split, t_scene *scene)
{
	char	**params[3];
	char	*size[2];
	int		error;

	if (ft_len(split) != 6 || ft_cylinder_checker(split))
		return (2);
	params[0] = ft_fast_split(ft_to_space(split[1]));
	params[1] = ft_fast_split(ft_to_space(split[2]));
	params[2] = ft_fast_split(ft_to_space(split[5]));
	size[0] = split[4];
	size[1] = split[3];
	if (params[0] == NULL || params[1] == NULL || params[2] == NULL
		|| ft_len(params[0]) != 3
		|| ft_len(params[1]) != 3
		|| ft_len(params[2]) != 3)
	{
		error = 2;
		if (params[0] == NULL || params[1] == NULL || params[2] == NULL)
			error = -1;
		free(params[0]);
		free(params[1]);
		free(params[2]);
		return (error);
	}
	return (ft_cylinder_parse(params, size, scene));
}
