/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 04:05:40 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 00:02:29 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_isnumeric(char *str)
{
	int	i;

	i = 0;
	while (*(str + i) != '\0')
	{
		if (!ft_isdigit(*(str + i)))
			return (0);
		i++;
	}
	return (1);
}

int	ft_color_checker(char **color)
{
	int	i;

	i = 0;
	while (color[i] != NULL)
	{

		if (!ft_isnumeric(color[i])
				|| ft_atoi(color[i]) > 255)
			return (1);
		i++;
	}
	return (0);
}

int	ft_length_checker(t_vec3 axis)
{
	double	len;

	len = sqrt(ft_dot(axis, axis));
	if (fabs(len - 1) > 0.01)
		return (1);
	return (0);
}

int	ft_coords_checker(char *coord)
{
	char	*tmp;
	int	i;

	i = 0;
	tmp = coord;
	while (tmp != NULL)
	{
		tmp = ft_strchr(tmp, ',');
		i += tmp != NULL;
		tmp = tmp + (tmp != NULL);
		if (i > 2)
			return (1);
	}
	return (0);
}

int	ft_coords_float_checker(char **coords)
{
	int	i;

	i = 0;
	while (coords[i] != NULL)
	{
		if (ft_float_checker(coords[i]))
			return (1);
		i++;
	}
	return (0);
}
