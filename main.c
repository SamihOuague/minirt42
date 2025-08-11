/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:12:11 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:17:55 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	ft_ray_direction(t_vec3 xy, t_elt *params)
{
	double	x;
	double	y;
	double	fov;

	fov = (*params).scene.camera.fov;
	x = (*params).aspect_r * (((xy.x + 0.5) / (*params).width) * 2 - 1);
	x = x * tan(ft_radian(fov / 2));
	y = ((xy.y + 0.5f) / (*params).height * 2.0f - 1.0f);
	y = y * tan(ft_radian(fov / 2.0f));
	return (ft_vec3(x, y, 1));
}

int	ft_compute_ray(t_vec3 matrix[3], int k, t_elt *params)
{
	t_vec3	xy;
	t_vec3	vector;
	t_ray	ray;	
	int		pixel;

	pixel = 0;
	xy.x = k % (*params).width;
	xy.y = k / (*params).width;
	vector = transform_ray(ft_ray_direction(xy, params), matrix);
	ft_init_ray(&ray, vector, (*params).scene.camera);
	if (ft_has_intersection((*params).scene.shapes, &ray, NULL))
		pixel = ft_light(&ray, &(*params).scene);
	return (pixel);
}

void	ft_create_image(t_elt *params)
{
	t_vec3	matrix[3];
	int		k;
	int		size;

	k = 0;
	size = (*params).width * (*params).height;
	ft_lookat(matrix, (*params).scene.camera.direction);
	while (k < size)
	{
		ft_pixel_put(&(*params).data_addr,
			k % (*params).width,
			(*params).height - 1 - (k / (*params).width),
			(*params).size_line,
			(*params).bpp,
			ft_compute_ray(matrix, k, params));
		k++;
	}
}

int	main(int argc, char **argv)
{
	t_elt	params;
	t_ray	ray;

	params.width = WIDTH;	
	params.height = HEIGHT;
	params.aspect_r = (double)params.width / (double)params.height;
	if (argc != 2)
		return (1);
	else if (ft_minirt_init(argv[1], &params))
		return (1);
	params.mlx = mlx_init();
	if (params.mlx == NULL)
	{
		ft_lstclear(&params.scene.shapes, &ft_free_content);
		return (1);
	}
	params.win = mlx_new_window(params.mlx,
			params.width, params.height, "MiniRT");
	params.img_ptr = mlx_new_image(params.mlx, params.width, params.height);
	params.data_addr = mlx_get_data_addr(params.img_ptr,
			&params.bpp, &params.size_line, &params.endian);
	ft_create_image(&params);
	ft_run_loop(&params, params.width, params.height);
	return (0);
}
