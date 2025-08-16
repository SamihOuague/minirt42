/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:50:28 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/16 21:03:17 by souaguen         ###   ########.fr       */
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
	t_vec3		i;
	double		intensity;

	v = ft_sum((*ray).from, ft_product((*ray).direction, (*ray).hit.distance));
	lm = ft_normalize(ft_sub((*scene).light.origin, v));
	n = (*ray).hit.normal;
	intensity = ft_dot(lm, n);
	if (intensity < 0 || ft_is_shadow(*ray, (*scene).light.origin,
			(*scene).shapes) || (*scene).cla[1] == 0)
		intensity = 0;
	intensity = (intensity * (*scene).light.intensity);
	i = ft_vec3(intensity + (*scene).ambient * ((*scene).color.x / 255.0f),
			intensity + (*scene).ambient * ((*scene).color.y / 255.0f),
			intensity + (*scene).ambient * ((*scene).color.z / 255.0f));
	if (i.x > 1)
		i.x = 1;
	if (i.y > 1)
		i.y = 1;
	if (i.z > 1)
		i.z = 1;
	return (ft_get_rgb((*ray).hit.pixel.x * i.x,
			(*ray).hit.pixel.y * i.y, (*ray).hit.pixel.z * i.z));
}

int	ft_has_intersection(t_list *shapes, t_ray *ray, void *exclude)
{
	t_hitpoint	hit;
	t_list		*cursor;
	t_shape		*content;

	(void) exclude;
	cursor = shapes;
	hit.distance = 10000;
	(*ray).from = ft_sum((*ray).from, ft_product((*ray).direction, 1e-6));
	while (cursor != NULL)
	{
		content = (*cursor).content;
		if ((*content).has_inter((*content).object, ray)
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
	return (ft_set_hit(hit, ray));
}
