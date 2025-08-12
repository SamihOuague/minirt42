/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:07:00 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/12 02:57:21 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_cy_normal(t_cylinder cy, t_ray *ray)
{
	t_vec3	normal;
	t_vec3	hit;
	double	t;

	hit = ft_product((*ray).direction, (*ray).hit.distance);
	t = ft_dot(cy.axis, ft_sub(hit, cy.origin));
	normal = ft_sub(ft_sub(hit, ft_product(cy.axis, t)), cy.origin);
	normal = ft_product(normal, 1.0f / sqrt(ft_dot(normal, normal)));
	(*ray).hit.normal = normal;
	return (1);
}

int	ft_caps_intersection(t_cylinder cy, t_ray *ray)
{
	t_vec3	c_top;
	t_vec3	hit;
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
	hit = ft_sub(ft_product((*ray).direction, d[0]), c_top);
	(*ray).hit.distance = d[0];
	(*ray).hit.normal = cy.axis;
	if (ft_dot(hit, hit) < pow(cy.radius, 2) && d[0] > 0 && d[0] <= d[1])
		return (1);
	hit = ft_sub(ft_product((*ray).direction, d[1]), cy.origin);
	(*ray).hit.normal = ft_product(cy.axis, -1);
	(*ray).hit.distance = d[1];
	if (ft_dot(hit, hit) < pow(cy.radius, 2) && d[1] > 0)
		return (1);
	return (0);
}

void	ft_cylinder_vars_init(t_cylinder *cy, t_vec3 *cross_d,
		t_vec3 *equation, t_ray *ray)
{
	(*cy).origin = ft_sub((*cy).origin, (*ray).from);
	*cross_d = ft_cross_product((*ray).direction, (*cy).axis);
	(*equation).x = ft_dot(*cross_d, *cross_d);
	(*equation).y = ft_dot(*cross_d,
			ft_cross_product((*cy).origin, (*cy).axis));
	(*equation).z = ((*equation).x * pow((*cy).radius, 2))
		- (ft_dot((*cy).axis,
				(*cy).axis) * pow(ft_dot((*cy).origin, *cross_d), 2));
}

int	ft_cylinder_intersection(void *cylinder, t_ray *ray)
{
	t_cylinder	cy;
	t_vec3		cross_d;
	t_vec3		equation;
	double		t[2];

	cy = *(t_cylinder *)cylinder;
	ft_cylinder_vars_init(&cy, &cross_d, &equation, ray);
	(*ray).hit.shape_addr = cylinder;
	if (equation.z < 0 || equation.x == 0)
		return (ft_caps_intersection(cy, ray));
	t[0] = (equation.y - sqrt(equation.z)) / equation.x;
	t[1] = (equation.y + sqrt(equation.z)) / equation.x;
	t[1] = ft_dot(cy.axis,
			ft_sub(ft_product((*ray).direction, t[0]), cy.origin));
	if (t[1] <= 0 || t[1] >= cy.height)
		return (ft_caps_intersection(cy, ray));
	(*ray).hit.distance = t[0];
	return (ft_cy_normal(cy, ray));
}

t_cylinder	ft_cylinder(t_vec3 origin, t_vec3 axis,
				double height, double radius)
{
	t_cylinder	cy;

	cy.axis = axis;
	cy.origin = origin;
	cy.height = height;
	cy.radius = radius;
	return (cy);
}
