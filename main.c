/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regien <gmalpart@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:13:40 by regien            #+#    #+#             */
/*   Updated: 2018/02/07 05:33:00 by gmalpart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

/*
	vas  a usar estructuras como negro
*/

// cambiar escapes de fillit
// MENSAJES PERSONALIZADOS - CODIGO DE ERROR
//
int			my_key_function(int keycode, t_total *envi)
{
	printf("key event %d\n", keycode);
	if (keycode == KEY_ESC)
		destroy_exit(ESCAPE, "gracias por usar esta pendejada\n", envi->mlx, envi->win);
	if (keycode == KEY_C)
		mlx_clear_window(envi->mlx, envi->win);
	if (keycode == 2)
		envi->theta += 00.01;
	if (keycode == 0)
		envi->theta -= 00.01;
	if (keycode == 13)
		envi->phi += 00.01;
	if (keycode == 1)
		envi->phi -= 00.01;
	if (keycode == 14)
		envi->psi += 00.01;
	if (keycode == 12)
		envi->psi -= 00.01;
//	redraw(envi);
	return (0);
}

int			mouse_hook(int keycode, t_total *envi)
{
	printf("key event %d\n", keycode);
	if (keycode == 1)
		;
//		envi->phi -= 00.01;
	return (0);
}

// for now only works with parsing the name, now we are opening the file
// and build a valid matrix and start creating the structure
// FIRST PART PARSER
int			parser_argv(char *str)
{
	int		i;
	int		dots;

	dots = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_strlen(str) == 4)
			return (0);
		if (str[i] == '.')
			dots++;
		if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t' || dots >= 2)
			return (0);
	}
	if ((ft_strequ((ft_strstr(str, ".fdf")), ".fdf")) == 0)
		return (0);
	return (1);
}

int			count_splt(char **str)
{
		int	i;

		i = 0;
		while (str[i] != NULL)
			i++;
		return (i);
}

// NO ENDING | suppose to have a list as an argument to storage the linked list
int		splitter(char *str, t_total *envi)
{
	static char	**temp;
	int					i;

	i = -1;
	printf("matrix = %i\n", count_splt(ft_strsplit(str, ' ')));
	temp = ft_strsplit(str, ' ');
	// tamaño calculado
	if (envi->colum != 0)
	{
		if (envi->colum != count_splt(temp))
			general_exit(-1, "invalid map\n");
	}
	else
		envi->colum = count_splt(temp);
	i = -1;
	while (++i < envi->colum)
		free(temp[i]);
	// calcular de que tamano es el doble pointer
//	while (++i < envi->row)
//		add_list(list, temp[i]);
	return (1);
}

// take care of is_valid_hex || NOT HERE, IN THE SPLIT
int			parser_line(char *line)
{
	int i;

	i = -1;
	while (line[++i])
	{
		if (i == 0 && line[i] == ' ')
			return (0);
		if (line[i] == '\t')
			return (0);
// no todo los mapas deben ser tan exactos
//		if (line[i] == ' ')
//			if (line[i + 1] == ' ' || line[i + 1] == '\0')
//				return (0);
		if ((line[i] >= 'g' && line[i] <= 'z') || \
		(line[i] >= 'G' && line[i] <= 'Z'))
			return (0);
	}
	return (1);
}


// this is for parsing colors
/*
int			parser_island(char *island)
{
	int		i;

	i = -1;
	while(island[++i])
	{
		if (island[i] == ',')
			if (island[i + 1] == '0')
				if (island[i + 2] == 'x')
					
	}
}
*/

int			parser_file(char *str, t_total *envi)
{
	int		fd;
	static char	*line;
//	t_total		*envi;
	
//	envi = *envire;
	envi->row = 0;
	envi->colum = 0;
	if ((fd = open(str, O_RDONLY)) < 0)
			general_exit(-1, "invalid file\n");
	// change to if so only reads once / testing only
	printf("PENDEJADA\n");
	while ((get_next_line(fd, &line) > 0))
	{
		(envi->row)++;
		printf("matrix->row = %d\n", envi->row);
		if (parser_line(line) == 0 || splitter(line, envi) == 0)
		{
		//	printf("falla, falla en el parser dentro\n");
			return (0);
			// returning just for testing only
			// funcion para agregar a lista y setear matrix number
		}
		free(line);
	}
	close(fd);
	return (1);
}
/*
t_coord		*set_coord(int z)
{
	t_coord	*coord;

	if (!(coord = ft_memalloc(sizeof(t_coord))))
		exit(-1);
	coord->x = 0;
	coord->y = 0;
	coord->z = (float)z;
	coord->color = 0xFFFFFF;
	return (coord);
}

void		set_shit(t_coord  *coord, int z)
{

	coord->x = 0;
	coord->y = 0;
//	coord->z = (float)z;
	coord->z = z;
	printf("z = |%f|", coord->z);
	coord->color = 0xFFFFFF;
}
*/


// me llego al pincho y lo cambie todo a linked list
t_coord		*init_coord(t_total *envi)
{
	t_coord	*holder;
	int i;
	float *hol;
	int		*holcolor;
//	t_total *envi;

//	envi = *enviore;
	i = -1;
	holder = (t_coord*)ft_memalloc(sizeof(t_coord));
//	hol = holder->x;
	holder->x = ft_memalloc(sizeof(float) * (envi->row * envi->colum));
	while (++i < envi->row * envi->colum)
		holder->x[i] = 0;
//	hol = holder->y;
	holder->y = ft_memalloc(sizeof(float) * (envi->row * envi->colum));
	i = -1;
	while (++i < envi->row * envi->colum)
		holder->y[i] = 0;
//	hol = holder->z;
	holder->z = ft_memalloc(sizeof(float) * (envi->row * envi->colum));
	i = -1;
	while (++i < envi->row * envi->colum)
		holder->z[i] = 0;
//	holcolor = holder->color;
	holder->color = ft_memalloc(sizeof(int) * (envi->row * envi->colum));
	i = -1;
	while (++i < envi->row * envi->colum)
		holder->color[i] = 0;
	return (holder);
}

void		set_coordz(t_coord *envi, int i, char *value)
{
//	t_coord	*envi;
//	t_total *pendejada;
	float	*holx;
	float	*holy;
	float	*holz;
	int		*colorhol;

//	pendejada = *envi;
//	envi = envi->coord;
//	holx = envi->x[];
//	holx[i] = (float)0;
	envi->x[i] = 0;
//	holy = envi->y;
//	holy[i] = (float)0;
	envi->y[i] = 0;
//	holz = envi->z;
//	holz[i] = (float)atoi(value);
	envi->z[i] = (float)atoi(value);
//	colorhol = envi->color;
//	colorhol[i] = 0x012346;
	envi->color[i] = 0x012345;
}

/*
void		coord_add_listback(t_coord **list, t_coord *new)
{
	t_coord		*iter;

	if (!new || !list)
		return ;
	iter = *list;
	while (iter->next != NULL)
		iter = iter->next;
	iter->next = new;

}

void		adder(t_coord **list, char *str)
{
	if (*list)
		coord_add_listback(list, create_node(str));
	else
		*list = create_node(str);
}


t_coord		*create_node(char *str)
{
	t_coord *new;
	
	new = ft_memalloc(sizeof(t_coord));
	new->x = 0;
	new->y = 0;
	new->z = (float)ft_atoi(str);
	new->color = 0;
	new->next = NULL;
	return (new);
}
*/

void		storage(char *arg, t_total *envi)
{
	int		fd;
	static char	*line;
	static char **temp;
	int		y;
	int		x;
///	t_total *envi;

//	envi = *enviore;
	if ((fd = open(arg, O_RDONLY)) < 0)
			general_exit(-1, "invalid file\n");
	printf("just checking, row = |%d| column = |%d|\n", envi->row, envi->colum);
//	y = -1;
//	coord = (t_coord**)ft_memalloc(sizeof(t_coord*));
//	envi->coord = (t_coord*)ft_memalloc(sizeof(t_coord) * (envi->row * envi->colum));

	envi->coord = init_coord(envi);

//	while (++y < envi->row)
//		envi->coord[y] = (t_coord*)ft_memalloc(sizeof(t_coord) * envi->colum);
	x =-1;
	while (get_next_line(fd, &line) > 0)
	{
		y = 0;
		temp = ft_strsplit(line, ' ');
		while (++x < envi->colum * envi->row && y < envi->colum)
		{
//			adder(&(envi->coord), temp[y]);
//			agrega lista;

			set_coordz(envi->coord, x, (temp[y]));
			y++;
		}
		free(line);
		for (y = 0 ; y < envi->colum; y++)
			free(temp[y]);
	}
	ft_putstr("done\n");
	close(fd);
}

void		parser(char *arg, t_total *envi)
{
	t_coord *temp;

	if (parser_argv(arg) == 0 || parser_file(arg, envi) == 0)
		general_exit(-1, "invalid file\n");
	else
		storage(arg, envi);
}

void		loophole(t_total *envi)
{
	envi->theta = 0;
	envi->phi = 0;
	envi->psi = 0;
	mlx_put_image_to_window(envi->mlx, envi->win, envi->img, 0, 0);
	mlx_hook(envi->win, 2, 0, my_key_function, envi);
	mlx_hook(envi->win, 4, 5, mouse_hook, envi);
	mlx_loop(envi->mlx);
}

int				main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	void		*img;

	t_total		*envi;

	envi = ft_memalloc(sizeof(t_total));
// parser
	if (argc != 2)
		fillit_print_usage(argv[0]);
	parser(argv[1], envi);
	envi->setting = ft_memalloc(sizeof(t_bresen));
//	envi->coord = ft_memalloc(sizeof(t_coord) * 12);
//	envi->dest = ft_memalloc(sizeof(t_coord) * 12);
	envi->mlx = mlx_init();
	envi->win = mlx_new_window(envi->mlx, WINW, WINH, "testing my shit");

	envi->img = mlx_new_image(envi->mlx, WINW, WINH);
	envi->pix = (int*)mlx_get_data_addr(envi->img, &(envi->bits), \
	&(envi->s_line), &(envi->endian));

//	m3d_init(envi);
//	mat_identity(envi->matrix1);
	int y = -1;
	int x = -1;

/*	t_coord *temp;
	
	temp = envi->coord;
	while (temp->next != NULL)
	{
		y++;
		temp = temp->next;
	}

	printf ("y = |%d|", y);
//	temp = temp->next;ft_memalloc
//	temp = ft_memalloc(sizeof(float) * 15);
//	temp[0] = 34;
	printf("pendejada\n");
	printf("pendejada z = |%f|\n", envi->coord->next->next->z);
*/


/*	while (++y < envi->row)
	{
		x = -1;
		while (++x < envi->colum)
		{
//		temp = &(envi->coord[y][x]);
		printf("pendejada z = |%f|\n", &(envi->coord[y][x]).z);
		}
	}
*/
//	mlx_mouse_hook(envi->win, my_key_function, envi);
	printf("pendejada = |%f|\n", envi->phi);
	while (++x < 25)
		printf("pendejada = |%f|\n", envi->coord->z[x]);
//	redraw(envi);
	loophole(envi);
}