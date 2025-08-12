/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:50:28 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/12 02:55:57 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_get_rgb(int r, int g, int b)
{
	return ((((r << 8) + g) << 8) + b);
}

void	ft_pixel_put(char **data_addr, t_vec3 v, t_elt *params, int pixel)
{
	int	x;
	int	y;
	int	bpp;
	int	s_line;

	x = v.x;
	y = v.y;
	bpp = (*params).bpp;
	s_line = (*params).size_line;
	*(unsigned int *)((*data_addr) + (s_line * y) + (x * (bpp / 8))) = pixel;
}

int	ft_is_shadow(t_ray ray, t_vec3 light, t_list *shapes)
{
	t_vec3	hit;
	t_ray	shadow;
	double	light_d;

	hit = ft_sum(ray.from, ft_product(ray.direction, ray.hit.distance));
	shadow.direction = ft_normalize(ft_sub(light, hit));
	shadow.from = hit;
	light = ft_sub(light, hit);
	light_d = sqrt(ft_dot(light, light));
	if (ft_has_intersection(shapes, &shadow, ray.hit.shape_addr)
		&& light_d > shadow.hit.distance)
		return (1);
	return (0);
}

int	ft_light(t_ray *ray, t_scene *scene)
{
	t_vec3		v;
	t_vec3		lm;
	t_vec3		n;
	double		intensity;

	v = ft_sum((*ray).from, ft_product((*ray).direction, (*ray).hit.distance));
	lm = ft_normalize(ft_sub((*scene).light.origin, v));
	n = (*ray).hit.normal;
	intensity = ft_dot(lm, n);
	if (intensity < 0 || ft_is_shadow(*ray, (*scene).light.origin,
			(*scene).shapes))
		intensity = 0;
	intensity = (intensity * (*scene).light.intensity) + (*scene).ambient;
	if (intensity > 1)
		intensity = 1;
	return (ft_get_rgb((*ray).hit.pixel.x * intensity,
			(*ray).hit.pixel.y * intensity,
			(*ray).hit.pixel.z * intensity));
}

int	ft_has_intersection(t_list *shapes, t_ray *ray, void *exclude)
{
	t_hitpoint	hit;
	t_list		*cursor;
	t_shape		*content;

	cursor = shapes;
	hit.distance = 10000;
	while (cursor != NULL)
	{
		content = (*cursor).content;
		if ((*content).object != exclude
			&& (*content).has_inter((*content).object, ray)
			&& (*ray).hit.distance > 0)
		{
			if ((*ray).hit.distance < hit.distance)
			{
				hit = (*ray).hit;
				hit.pixel = (*content).color;
			}
		}
		cursor = (*cursor).next;
	}
	(*ray).hit = hit;
	if (hit.distance < 10000 && hit.distance > 0)
		return (1);
	return (0);
}
