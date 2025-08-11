/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 04:50:28 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 18:30:15 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int     ft_get_rgb(int r, int g, int b)
{
        return (((r << 8) + g) << 8) + b;
}

void	ft_pixel_put(char **data_addr, int x, int y, int s_line, int bpp, int pixel)
{
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
	t_hitpoint	hit;
	t_vec3		v;
	t_vec3		lm;
	t_vec3		n;
	double		intensity;
	int		pixel;
	t_light		light;
	t_list		*shapes;

	light = (*scene).light;
	shapes = (*scene).shapes;
	v = ft_sum((*ray).from, ft_product((*ray).direction, (*ray).hit.distance));
	hit = (*ray).hit;
	lm = ft_normalize(ft_sub(light.origin, v));
	n = hit.normal;
	intensity = ft_dot(lm, n);
	if (intensity < 0 || ft_is_shadow(*ray, light.origin, shapes))
		intensity = 0;
	intensity = (intensity * light.intensity) + (*scene).ambient;
	if (intensity > 1)
		intensity = 1;
	pixel = ft_get_rgb(hit.pixel.x * intensity,
			hit.pixel.y * intensity,
		       	hit.pixel.z * intensity);
	return (pixel);
}

int	ft_has_intersection(t_list *shapes, t_ray *ray, void *exclude)
{
	t_list	*cursor;
	t_list	*tmp;
	t_shape	*content;
	t_hitpoint	hit;

	hit.distance = 10000;
	cursor = shapes;
	while (cursor != NULL)
	{
		content = (*cursor).content;
		if ((*content).object != exclude 
			&& (*content).hasInter((*content).object, ray)
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
