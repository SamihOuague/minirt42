/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:07:00 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/17 22:21:51 by souaguen         ###   ########.fr       */
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
	t[0] = (equation.y + sqrt(equation.z)) / equation.x;
	t[1] = (equation.y - sqrt(equation.z)) / equation.x;
	if (t[0] < 0 && t[1] < 0)
		return (ft_caps_intersection(cy, ray));
	if (t[0] > t[1] && t[1] > 0)
		t[0] = t[1];
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
