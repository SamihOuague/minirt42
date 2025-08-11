/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shapes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 04:51:39 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:40:51 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_shapes_alloc(void **object, t_shape **shape, unsigned int obj_size)
{
	*object = malloc(obj_size);
	*shape = malloc(sizeof(t_shape));
	if (*object == NULL || *shape == NULL)
	{
		free(object);
		free(shape);
	}
}

void	ft_shape_init(t_shape **shape, void *obj,
		t_vec3 color, void (f)(t_shape **))
{
	(**shape).object = obj;
	(**shape).color = color;
	f(shape);
}

t_shape	*ft_create_sphere(t_vec3 origin, double radius, t_vec3 color)
{
	t_sphere	*sphere;
	t_shape		*shape;

	ft_shapes_alloc((void **)&sphere, &shape, sizeof(t_sphere));
	if (sphere == NULL || shape == NULL)
		return (NULL);
	*sphere = ft_sphere(origin, radius);
	ft_shape_init(&shape, sphere, color, &ft_sphere_shape);
	return (shape);
}

t_shape	*ft_create_cylinder(t_vec3 base, t_vec3 axis,
		double size[2], t_vec3 color)
{
	t_cylinder	*cylinder;
	t_shape		*shape;

	ft_shapes_alloc((void **)&cylinder, &shape, sizeof(t_cylinder));
	if (cylinder == NULL || shape == NULL)
		return (NULL);
	*cylinder = ft_cylinder(base, axis, size[0], size[1]);
	ft_shape_init(&shape, cylinder, color, &ft_cylinder_shape);
	return (shape);
}

t_shape	*ft_create_plane(t_vec3 axis, t_vec3 point, t_vec3 color)
{
	t_plane		*plane;
	t_shape		*shape;

	ft_shapes_alloc((void **)&plane, &shape, sizeof(t_plane));
	if (plane == NULL || shape == NULL)
		return (NULL);
	*plane = ft_plane(axis, point);
	ft_shape_init(&shape, plane, color, &ft_plane_shape);
	return (shape);
}
