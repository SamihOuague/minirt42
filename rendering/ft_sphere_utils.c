/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 04:50:38 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 00:17:52 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

int	ft_sphere_normal(t_sphere sphere, t_ray *ray)
{
	t_vec3	normal;
	t_vec3	hit;

	hit = ft_product((*ray).direction, (*ray).hit.distance);
	sphere.origin = ft_sub(sphere.origin, (*ray).from);
	normal = ft_sub(hit, sphere.origin);
	(*ray).hit.normal = ft_normalize(normal);	
	return (1);
}

int		ft_sphere_intersection(void *sphere, t_ray *ray)
{
	t_sphere	s;
	t_vec3		equation;
	double		dis;
	double		t[2];
	t_vec3		tmp;

	s = *(t_sphere *)sphere;
	tmp = ft_sub((*ray).from, s.origin);
	equation.x = ft_dot((*ray).direction, (*ray).direction);
	equation.y = 2 * ft_dot((*ray).direction, tmp);
	equation.z = ft_dot(tmp, tmp) - pow(s.radius, 2);
	dis = pow(equation.y, 2) - 4 * (equation.x * equation.z);
	if (dis < 0)
		return (0);
	t[0] = -equation.y / (2 * equation.x);
	t[1] = t[0];
	if (dis > 0)
		dis = sqrt(dis);
	t[0] = (-equation.y + dis) / (2 * equation.x);
	t[1] = (-equation.y - dis) / (2 * equation.x);
	if (t[0] > t[1])
		t[0] = t[1];
	(*ray).hit.distance = t[0];
	(*ray).hit.shape_addr = sphere;
	return (ft_sphere_normal(s, ray));
}

t_sphere	ft_sphere(t_vec3 origin, double radius)
{
	t_sphere	sphere;

	sphere.origin = origin;
	sphere.radius = radius;
	return (sphere);
}

void	ft_sphere_shape(t_shape **shape)
{
	if (shape == NULL || *shape == NULL)
		return ;
	(**shape).hasInter = &ft_sphere_intersection;
}
