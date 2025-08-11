/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 05:07:00 by souaguen          #+#    #+#             */
/*   Updated: 2024/10/27 14:08:45 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3          ft_cross_product(t_vec3 a, t_vec3 b)
{
        t_vec3  v;

        v.x = (a.y * b.z) - (a.z * b.y);
        v.y = (a.z * b.x) - (a.x * b.z);
        v.z = (a.x * b.y) - (a.y * b.x);
        return (v);
}

/*typedef struct s_cylinder
{
        t_vec3  axis;
        t_vec3  origin;
        double  height;
        double  radius;
}       t_cylinder;*/

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

t_vec3	ft_sum(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

int	ft_caps_intersection(t_cylinder cy, t_ray *ray)
{
	t_vec3	c_top;
	t_vec3	hit;
	double	den;
	double	num;
	double	c;
	double	d[2];

	//cy.axis = ft_normalize(cy.axis);
	c_top = ft_sum(cy.origin, ft_product(cy.axis, cy.height));
	den = ft_dot(cy.axis, (*ray).direction);
	if (fabs(den) <= 0.0001f)
		return (0);
	num = ft_dot(cy.axis, c_top);
	d[0] = num / den;
	num = ft_dot(cy.axis, cy.origin);
	d[1] = num / den;
	hit = ft_sub(ft_product((*ray).direction, d[1]), cy.origin);
	(*ray).hit.distance = d[1];
	(*ray).hit.normal = ft_product(cy.axis, -1);
	if (ft_dot(hit, hit) < pow(cy.radius, 2) && d[1] > 0)
		return (1);
	hit = ft_sub(ft_product((*ray).direction, d[0]), c_top);
	(*ray).hit.distance = d[0];
	(*ray).hit.normal = cy.axis;
	if (ft_dot(hit, hit) < pow(cy.radius, 2) && d[0] > 0)
		return (1);
	return (0);
}

int	ft_cylinder_intersection(void *cylinder, t_ray *ray)
{
	t_cylinder	cy;
	t_vec3		cross_d;
	t_vec3		equation;
	t_ray		caps_ray;
	double		t[2];

	cy = *(t_cylinder *)cylinder;	
	cy.origin = ft_sub(cy.origin, (*ray).from);	
	//cy.axis = ft_normalize(cy.axis);
	cross_d = ft_cross_product((*ray).direction, cy.axis);
	equation.x = ft_dot(cross_d, cross_d);
	equation.y = ft_dot(cross_d, ft_cross_product(cy.origin, cy.axis));
	equation.z = (equation.x * pow(cy.radius, 2)) - (ft_dot(cy.axis, cy.axis) * pow(ft_dot(cy.origin, cross_d), 2));
	caps_ray = *ray;
	(*ray).hit.shape_addr = cylinder;
	if (equation.z < 0 || equation.x == 0)
		return (ft_caps_intersection(cy, ray));
	t[0] = (equation.y - sqrt(equation.z)) / equation.x;
	t[1] = (equation.y + sqrt(equation.z)) / equation.x;
	//if (t[0] > t[1])
	//	t[0] = t[1];
	t[1] = ft_dot(cy.axis, ft_sub(ft_product((*ray).direction, t[0]), cy.origin));
	if (t[1] < 0 || t[1] >= cy.height)
		return (ft_caps_intersection(cy, ray));
	(*ray).hit.distance = t[0];	
	if (ft_caps_intersection(cy, &caps_ray) && caps_ray.hit.distance < t[0])
	{
		*ray = caps_ray;
		return (1);
	}
	return (ft_cy_normal(cy, ray));
}

t_cylinder	ft_cylinder(t_vec3 origin, t_vec3 axis, double height, double radius)
{
	t_cylinder	cy;

	cy.axis = axis;
	cy.origin = origin;
	cy.height = height;
	cy.radius = radius;
	return (cy);
}

void	ft_cylinder_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).hasInter = &ft_cylinder_intersection;
}
