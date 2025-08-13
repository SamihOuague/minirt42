/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ambient_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:34:43 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/13 01:35:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_ambient_checker(char **split)
{
	if (ft_float_checker(split[1]))
		return (1);
	else if (ft_coords_checker(split[2]))
		return (1);
	return (0);
}

int	ft_set_ambient(t_vec3 color, double intensity, t_scene *scene)
{
	(*scene).ambient = intensity;
	(*scene).color = color;
	return (0);
}

int	ft_ambient_parse(char *i, char **c, t_scene *s)
{
	t_vec3	color;
	double	intensity;
	int		error;	

	error = 0;
	if (ft_color_checker(c) || ft_float_checker(i))
		error = 4;
	if (!error)
	{
		color = ft_vec3(ft_to_double(c[0]),
				ft_to_double(c[1]),
				ft_to_double(c[2]));
		intensity = ft_to_double(i);
		if (intensity < 0.0f || intensity > 1.0f)
			error = 8;
		ft_set_ambient(color, intensity, s);
	}
	free(c);
	return (error);
}

int	ft_init_ambient(char **split, t_scene *scene)
{
	char	**color;
	char	*intensity;
	int		error;

	if ((*scene).cla[2] > 0)
		return (5);
	(*scene).cla[2] += 1;
	if (ft_len(split) != 3 || ft_ambient_checker(split))
		return (2);
	color = ft_fast_split(ft_to_space(split[2]));
	intensity = split[1];
	if (color == NULL || ft_len(color) != 3)
	{
		error = 4;
		if (color == NULL)
			error = -1;
		free(color);
		return (error);
	}
	return (ft_ambient_parse(intensity, color, scene));
}
