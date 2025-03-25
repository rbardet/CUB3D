/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelacou <hdelacou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 23:50:07 by rbardet-          #+#    #+#             */
/*   Updated: 2025/03/25 16:06:49 by hdelacou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// debug function to show all the data inside the main struct *cub
void	print_struct(t_cub *cub)
{
	printf("north texture : %p\n", cub->no_xpm);
	printf("south texture : %p\n", cub->so_xpm);
	printf("west texture : %p\n", cub->we_xpm);
	printf("east texture : %p\n", cub->ea_xpm);
	printf("door texture : %p\n", cub->do_xpm);
	printf("red floor : %d\n", cub->floor.red);
	printf("green floor : %d\n", cub->floor.green);
	printf("blue floor : %d\n", cub->floor.blue);
	printf("floor value :\n");
	printf("\033[48;2;%d;%d;%dm              \033[0m\n", cub->floor.red, cub->floor.green, cub->floor.blue);
	printf("red ceilling : %d\n", cub->ceil.red);
	printf("green ceilling : %d\n", cub->ceil.green);
	printf("blue ceilling : %d\n", cub->ceil.blue);
	printf("ceilling value :\n");
	printf("\033[48;2;%d;%d;%dm              \033[0m\n", cub->ceil.red, cub->ceil.green, cub->ceil.blue);
	printf("player x : %d\n", cub->player.pos_x);
	printf("player y : %d\n", cub->player.pos_y);
	printf("dir x : %f\n", cub->player.dir_x);
	printf("dir y : %f\n", cub->player.dir_y);
	printf("plane x : %f\n", cub->player.plane_x);
	printf("plane y : %f\n", cub->player.plane_y);
	printf("player spawn : %c\n", cub->spawn_view);
	printab(cub->map);
	exit (0);
}

// a boolean function that take the name of the map and move its cursor to
// the 4 last character to see if the map is a .cub file
// return TRUE if it is else return FALSE
t_bool	is_cub(char *argv)
{
	argv += ft_strlen(argv) - 4;
	if (!ft_strcmp(argv, ".cub"))
		return (TRUE);
	else
	{
		ft_putstr_fd("Error\nThe map is not a .cub\n", 2);
		return (FALSE);
	}
}

int	main(int argc, char **argv)
{
	t_cub	*cub;

	if (argc != 2)
	{
		ft_putstr_fd("Error\nYou need to pass one map.\n", 2);
		return (127);
	}
	if (!is_cub(argv[1]))
		return (127);
	cub = parse_struct(argv[1]);
	if (!cub)
		exit (127);
	open_window(cub);
	return (0);
}
