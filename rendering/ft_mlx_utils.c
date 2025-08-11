/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souaguen <souaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 21:46:49 by souaguen          #+#    #+#             */
/*   Updated: 2025/08/11 20:25:25 by souaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	close_n_clean(t_elt *param)
{
	ft_lstclear(&(*param).scene.shapes, &ft_free_content);
	mlx_clear_window((*param).mlx, (*param).win);
	mlx_destroy_image((*param).mlx, (*param).img_ptr);
	mlx_clear_window((*param).mlx, (*param).win);
	mlx_destroy_window((*param).mlx, (*param).win);
	mlx_destroy_display((*param).mlx);
	free((*param).mlx);
	exit(0);
}

int	hook(t_elt *param)
{
	close_n_clean(param);
	return (0);
}

int	key_hook_ptr(int key, t_elt *param)
{
	if (key == 65307)
		close_n_clean(param);
	return (3);
}

int	ft_minirt_init(char *filename, t_elt *params)
{
	int		fd;

	ft_set_scene(&(*params).scene);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (1);
	}
	ft_init_scene(fd, &(*params).scene);
	close(fd);
	if ((*params).scene.error != 0)
	{
		printf("Error code %d\n", (*params).scene.error);
		ft_lstclear(&(*params).scene.shapes, &ft_free_content);
		return (1);
	}
	return (0);
}
