/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: regien <gmalpart@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/31 19:13:40 by regien            #+#    #+#             */
/*   Updated: 2018/02/02 14:26:48 by gmalpart         ###   ########.fr       */
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


/*
t_list		*bitch_me_a_list(t_list **list, char **pendejada)
{
	t_list	*iter;
	t_node	*iterdata;

	if ()
}
*/

///		HELPER LINKED LIST FUNCTION

// NOT OPTIMAZED
t_list		*create_node(char *str)
{
	t_node		*new;

	if(!(new = ft_memalloc(sizeof(t_node))))
		return (0);
	new->x = ft_atoi(str);
	new->y = 0;
	new->z = 0;
	new->color = 0x00FFFFFF;
	return (ft_lstnew(new, sizeof(t_node)));
}

void		add_list(t_list **lista, char *str)
{
	if (*lista)
		ft_lst_addback(lista, create_node(str));
	else
		*lista = create_node(str);
}

// contador de cuanto es la matriz
int			count_splt(char **str)
{
		int	i;

		i = 0;
		while (str[i] != NULL)
			i++;
		return (i);
}

// NO ENDING | suppose to have a list as an argument to storage the linked list
int		splitter(char *str, t_list **list, t_matrx *matrix)
{
	static char	**temp;
	int					column;
	int					i;

	i = -1;
	printf("matrix = %i\n", count_splt(ft_strsplit(str, ' ')));
	temp = ft_strsplit(str, ' ');
	// tamaño calculado
	if (matrix->row != 0)
	{
		if (matrix->row != count_splt(temp))
			general_exit(-1, "invalid map\n");
	}
	else
		matrix->row = count_splt(temp);
	// calcular de que tamano es el doble pointer
	while (++i < matrix->row)
		add_list(list, temp[i]);
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
		if (line[i] == ' ')
			if (line[i + 1] == ' ' || line[i + 1] == '\0')
				return (0);
	//	if ((line[i] >= 'g' && line[i] <= 'z') || \
	//	(line[i] >= 'G' && line[i] <= 'Z'))
	//		return (0);
	}
	return (1);
}

// suposse to have a linked as an argument / storage purpose
int			parser_file(char *str, t_list **list, t_matrx **matrix)
{
	int		fd;
	char	*line;
	t_matrx	*holder;
//	static t_matrx		matrix;

	*matrix = ft_memalloc(sizeof(t_matrx));
	holder = *matrix;
	// HERE NULLIFYING THE LIST <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//	*list = NULL;
//	matrix = 0;

	if ((fd = open(str, O_RDONLY)) < 0)
			general_exit(-1, "invalid file\n");
	// change to if so only reads once / testing only
	printf("PENDEJADA\n");
	if ((get_next_line(fd, &line)) > 0)
	{
		// row ++ <- para determinar la distancia entra las pendejadas
		(holder->column)++;
		printf("matrix->column = %d\n", holder->column);
		if (parser_line(line) == 1 && splitter(line, list, holder) == 1)
		{
			printf("wowowowowbypass\n");
			// returning just for testing only
			return (1);
			// funcion para agregar a lista y setear matrix number
		}
		else
			return (0);
	}
	close(fd);
	return (0);
}

int				main(int argc, char **argv)
{
	void		*mlx;
	void		*win;
	void		*img;

//	t_list		*list;
//	t_env		*envi;
//	static t_matrx	*matrix;
	t_total		*envi;

// parser

/*
	if (argc != 2)
	{
		fillit_print_usage(argv[0]);
		return (0);
	}

	// allocating a matrix;
//	matrix = ft_memalloc(sizeof(t_matrx));

	if (parser_argv(argv[1]) == 0 || parser_file(argv[1], &list, &matrix) == 0)
	{
		general_exit(ESCAPE, "invalid file or map\n");
		return (0);
	}
*/
	envi = ft_memalloc(sizeof(t_total));
	envi->mlx = mlx_init();
	envi->win = mlx_new_window(envi->mlx, WINW, WINH, "testing my shit");
	envi->img = mlx_new_image(envi->mlx, WINW, WINH);
	envi->pix = (int*)mlx_get_data_addr(envi->img, &(envi->bits), \
	&(envi->s_line), &(envi->endian));

//	esta pendejada siempre esta activa, vale la pena activarla
	mlx_do_key_autorepeatoff(envi->mlx);
	mlx_hook(envi->win, 4, 0, my_key_function, envi);
	mlx_hook(envi->win, 2, 0, my_key_function, envi);
//	mlx_hook(envi->win, 1, 0, my_key_function, envi);
//	mlx_hook(envi->win, 10, 0, my_key_function, envi);
//	mlx_key_hook(envi->win, my_key_function, envi);

//	straight_line(200, 0,0, envi->mlx, envi->win);
//	straight_line_y(200, 200, 0, envi->mlx, envi->win);
//	b_line(300, 500, 600, 700, envi);

//	mlx_clear_window(mlx, win);
//	mlx_pixel_put(mlx, win, 200, 200, 0x00FFFFFF);
//	draw_circle(300, 300, 150, envi);

//	draw_circle_fill(300, 300, 50, envi);

//	multi loop hook, perfect for stuff like wolf3d and some super weird stuff
//	that you can do in this project.
//	mlx_loop_hook(envi->mlx, my_key_function, envi);
	printf("pendejada\n");

	b_line_3d(300, 300, 0, 500, 500, 0, envi);
// dunno why this doesnt work but with the img it doesnt
//	b_line(500, 500, 600, 300, envi);
	
	img = mlx_new_image(envi->mlx, 400, 400);
//	printf("data address = %s", mlx_get_data_addr(img, 14, 14, 1));
//	int		*bits;
//	int		*s_line;
	int		d, k;
	d = 0;
	k = 0;
	img = mlx_xpm_file_to_image(envi->mlx, "example1.xpm", &d, &k);
//	mlx_put_image_to_window(envi->mlx, envi->win, img, 0, 0);

//	bre_line(0, 0, 400, 100, envi);
//	bre_line(0, 0, 50, 10, envi);

//	u_bresen(0, 600, 800, 605, envi);
//	u_bresen(770, 800, 780, 0, envi);
//	u_bresen(700, 800, 780, 0, envi);
//	u_bresen(780, 800, 700, 0, envi);
	draw_line_ult(150, 200, 600, 0, envi);
	draw_line_ult(150, 200, 300, 0, envi);
	draw_line_ult(150, 200, 200, 0, envi);
	draw_line_ult(150, 200, 100, 0, envi);
	draw_line_ult(150, 200, 150, 190, envi);
	draw_line_ult(0, 700, 300, 0, envi);
	draw_line_ult(0, 700, 300, 0, envi);
	draw_line_ult(0, 400, 500, 400, envi);
	draw_line_ult(0, 400, 500, 400, envi);

/*
	draw_line(500, 500, 700, 300, envi);
	draw_line(100, 200, 400, 500, envi);
	draw_line(400, 400, 400, 500, envi);
	draw_line(700,300, 500, 100, envi);
*/
//	b_line(150/1 + 400, 150/1 + 400, 150/20 + 600, 150/20 + 600, envi);
	
	mlx_loop(envi->mlx);
}

// JUST REFERENCE MICHAEL CODE

