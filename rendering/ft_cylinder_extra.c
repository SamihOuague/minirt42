/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_extra.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 23:07:06 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/17 22:28:13 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_caps_normal_intersection(t_ray *ray, double d[2],
		t_vec3 c_top, t_cylinder cy)
{
	t_vec3	hit;

	hit = ft_sub(ft_product((*ray).direction, d[0]), c_top);
	(*ray).hit.distance = d[0];
	(*ray).hit.normal = cy.axis;
	if (ft_dot(hit, hit) < pow(cy.radius, 2) && d[0] > 0)
	{
		if (ft_dot((*ray).direction, (*ray).hit.normal) > 0)
			(*ray).hit.normal = ft_product((*ray).hit.normal, -1);
		return (1);
	}
	hit = ft_sub(ft_product((*ray).direction, d[1]), cy.origin);
	(*ray).hit.normal = cy.axis;
	(*ray).hit.distance = d[1];
	if (ft_dot(hit, hit) < pow(cy.radius, 2) && d[1] > 0)
	{
		if (ft_dot((*ray).direction, (*ray).hit.normal) > 0)
			(*ray).hit.normal = ft_product((*ray).hit.normal, -1);
		return (1);
	}
	return (0);
}

int	ft_caps_intersection(t_cylinder cy, t_ray *ray)
{
	t_vec3	c_top;
	double	den;
	double	num;
	double	d[2];

	c_top = ft_sum(cy.origin, ft_product(cy.axis, cy.height));
	den = ft_dot(cy.axis, (*ray).direction);
	if (fabs(den) <= 0.001f)
		return (0);
	num = ft_dot(cy.axis, c_top);
	d[0] = num / den;
	num = ft_dot(cy.axis, cy.origin);
	d[1] = num / den;
	if (ft_caps_normal_intersection(ray, d, c_top, cy))
		return (1);
	return (0);
}

void	ft_cylinder_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).has_inter = &ft_cylinder_intersection;
}
