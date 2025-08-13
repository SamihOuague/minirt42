/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_axis_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 22:50:26 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/13 02:48:23 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ft_cross_product(t_vec3 a, t_vec3 b)
{
	t_vec3	v;

	v.x = (a.y * b.z) - (a.z * b.y);
	v.y = (a.z * b.x) - (a.x * b.z);
	v.z = (a.x * b.y) - (a.y * b.x);
	return (v);
}

t_vec3	ft_sum(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

int	ft_set_hit(t_hitpoint hit, t_ray *ray)
{
	if (hit.distance < 10000 && hit.distance > 0)
	{
		if (ft_dot(hit.normal, (*ray).direction) > 0)
			hit.normal = ft_product(hit.normal, -1);
		(*ray).hit = hit;
		return (1);
	}
	return (0);
}
