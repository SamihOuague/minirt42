/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plan_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:44:26 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/12 23:27:35 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_plane_intersection(void *plane, t_ray *ray)
{
	t_plane	pl;
	double	d;
	double	num;
	double	den;

	pl = *(t_plane *)plane;
	den = ft_dot(pl.direction, (*ray).direction);
	if (fabs(den) <= 0.001f)
		return (0);
	num = ft_dot(pl.direction, ft_sub(pl.point, (*ray).from));
	d = num / den;
	(*ray).hit.distance = d;
	(*ray).hit.normal = ft_normalize(pl.direction);
	if (ft_dot((*ray).direction, (*ray).hit.normal) > 0)
		(*ray).hit.normal = ft_product((*ray).hit.normal, -1);
	(*ray).hit.shape_addr = plane;
	return (1);
}

t_plane	ft_plane(t_vec3 direction, t_vec3 point)
{
	t_plane	plane;

	plane.direction = direction;
	plane.point = point;
	return (plane);
}

void	ft_plane_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).has_inter = &ft_plane_intersection;
}
