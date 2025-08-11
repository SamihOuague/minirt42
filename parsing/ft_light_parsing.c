/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_light_parsing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 03:33:56 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:37:38 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_light_checker(char **split)
{
	if (ft_coords_checker(split[1]))
		return (1);
	else if (ft_float_checker(split[2]))
		return (1);
	else if (ft_coords_checker(split[3]))
		return (1);
	return (0);
}

int	ft_set_light(t_vec3 o, t_vec3 c, double i, t_scene *scene)
{
	(*scene).light.origin = o;
	(*scene).light.color = c;
	(*scene).light.intensity = i;
	return (0);
}

int	ft_light_parse(char **o, char **c, char *i, t_scene *s)
{
	t_vec3	origin;
	t_vec3	color;
	double	intensity;
	int		error;	

	error = 0;
	if (ft_coords_float_checker(o)
		|| ft_coords_float_checker(c)
		|| ft_float_checker(i))
		error = 4;
	if (!error)
	{
		origin = ft_vec3(ft_to_double(o[0]),
				ft_to_double(o[1]),
				ft_to_double(o[2]));
		color = ft_vec3(ft_to_double(c[0]),
				ft_to_double(c[1]),
				ft_to_double(c[2]));
		intensity = ft_to_double(i);
		if (intensity < 0.0f || intensity > 1.0f)
			error = 8;
		ft_set_light(origin, color, intensity, s);
	}
	free(o);
	free(c);
	return (error);
}

int	ft_init_light(char **split, t_scene *scene)
{
	char	**origin;
	char	**color;
	char	*intensity;
	int		error;

	if ((*scene).cla[1] > 0)
		return (5);
	(*scene).cla[1] += 1;
	if (ft_len(split) != 4 || ft_light_checker(split))
		return (2);
	origin = ft_fast_split(ft_to_space(split[1]));
	color = ft_fast_split(ft_to_space(split[3]));
	intensity = split[2];
	if (origin == NULL
		|| color == NULL
		|| ft_len(origin) != 3
		|| ft_len(color) != 3)
	{
		error = 4;
		if (origin == NULL || color == NULL)
			error = -1;
		free(origin);
		free(color);
		return (error);
	}
	return (ft_light_parse(origin, color, intensity, scene));
}
