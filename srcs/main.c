/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/05 14:17:42 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/02/05 18:18:58 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "doom.h" 

/*void visual(int i, t_input *data, double rotx, double rotz)
{
    double a;  
    double b;
    double dist;

}*/


/*t_ray   process_ray(double  rotx, double rotz, t_fdot pos_player)
{
    return (ray);
}*/

/*t_dot define_way(t_fdot angle)
{
    t_dot way;
    if (angle.x > M_PI_2 && angle.x < m_3PI_2)
        way.x = -1;
    else
        way.x = 1;
    if (angle.y > M_PI_2 && angle.y < m_3PI_2)
        way.x = -1;
    else
        way.x = 1;
    if (angle.x > M_PI_2 && angle.x < m_3PI_2)
        way.x = -1;
    else
        way.x = 1; 
}*/


/*t_fov *creat_fov(t_input *data)
{
    int i;
    t_fov *new;
    int max;
    int max_min;
    int thread;

    max = data->win_h * data->win_w;
    max_min = max - 1;
    thread = 0;
    new = malloc(sizeof(t_fov));
    data->fov = new;
    i = -1;
    while(++i < max)
    {
        if (!(i = max_min))
            new->next = malloc(sizeof(t_fov));
        if (i = thread * (data->win_h * data->win_w / NB_THREAD))
        {
            data->thread_tab[thread].fov = new;
            thread++;
        }
        new->rotx = data->alpha_x + (X_VIEW / 2 - ((data->win_w - i % data->win_w) / data->win_w) * X_VIEW);
        new->roty = data->alpha_z + (Z_VIEW / 2 - ((data->win_h - i / data->win_h) / data->win_h) * Z_VIEW);
        new = new->next;
    }
}*/

/*void raycast(t_thread* thread)
{
    printf("thread\n");
    printf("Thread : %d\n", thread->index);
    printf("start = %d, end = %d, index = %d\n",thread->i_start, thread->i_end, thread->index);
    if (!(thread->render = SDL_CreateRenderer(thread->inputs->window, -1, SDL_RENDERER_ACCELERATED)))
        printf("Erreur render\n");
	while(thread->i_start < thread->i_end)
	{
        visual(thread->i_start, thread->inputs, thread->inputs->dir.x + thread->fov->rotx, thread->inputs->dir.y + thread->fov->roty);
        SDL_RenderDrawPoint(thread->render, thread->i_start % thread->inputs->win_w, thread->i_start / thread->inputs->win_w);
        thread->i_start++;
	}
    SDL_RenderPresent(thread->render);
    SDL_DestroyRenderer(thread->render);
}*/

/*void thread_start(t_input	*data)
{
	int i;
	i = 0;
	while(i < NB_THREAD)
	{
		data->thread_tab[i].i_start = i * (data->win_h * data->win_w / NB_THREAD);
		data->thread_tab[i].i_end = (i + 1) * (data->win_h * data->win_w / NB_THREAD);
		data->thread_tab[i].inputs = data;
        data->thread_tab[i].index = i;
		pthread_create(&data->thread_tab[i].thread, NULL,
		&raycast, &data->thread_tab[i]);
		i++; 
	}
    printf("end\n");
	i = 0;
	while (i <= NB_THREAD)
		pthread_join(data->thread_tab[i++].thread, NULL);
}*/

t_ray *tab_ray(int nbrpix, t_input *data)
{
    t_ray *new;
    int i;

    i = 0;
    new = malloc(sizeof(t_ray) * nbrpix);
    while (i < data->win_h * data->win_w)
    {
        new[i].x = 1;
       //new[i].y = (X_VIEW / 2 - (double)(i % data->win_w / data->win_w) * X_VIEW);
        //[i].z = (Z_VIEW / 2 - ((data->win_h - (double)(i / data->win_h)) / data->win_h) * Z_VIEW);
        new[i].y = (-X_VIEW / 2 + i % data->win_w / (double)data->win_w * X_VIEW);
        new[i].z = (Z_VIEW / 2 - i / data->win_h / (double)data->win_h * Z_VIEW);
	    //printf("--%lf	%lf	%lf\n", new[i].x, new[i].y, new[i].z);
        i++;
    }
    return (new);
}

int		init_var(t_input *inputs)
{
	inputs->win_w = 1980;
	inputs->win_h = 1080;
	//fill_texture_tab(inputs);
	inputs->mlx_ad = mlx_init();
	inputs->win_ad = mlx_new_window(inputs->mlx_ad, inputs->win_w,
	inputs->win_h, "Doom Nukem");
	inputs->im.ad = mlx_new_image(inputs->mlx_ad, inputs->win_w, inputs->win_h);
	inputs->im.tab = (int *)mlx_get_data_addr(inputs->im.ad,
	&(inputs->im.bits_per_pixel), &(inputs->im.size_line),
	&(inputs->im.endian));
	return (1);
}

/*int Debugfct(t_poly *poly)
{    
    t_fdot a = (t_fdot){.x = 1, .y = -2, .z = 2};
    t_fdot b = (t_fdot){.x = 1, .y = -2, .z = -2};
    t_fdot c = (t_fdot){.x = 5, .y = 2, .z = 0};
    // t_fdot a = (t_fdot){.x = 1, .y = 1, .z = 2};
    // t_fdot b = (t_fdot){.x = 1, .y = -0.5, .z = 2};
    // t_fdot c = (t_fdot){.x = 1, .y = 0, .z = -2};
    t_fdot tab[NBR_PPOLY];
    poly->next = NULL;
    printf("seg?\n");
    poly->finaldot3d[0] = a;
    poly->finaldot3d[1] = b;
    poly->finaldot3d[2] = c;
    poly->nbrpoly = 3;
    return(1);

}*/

/*
**-------------------------------------------------PRINT OBJ PARSE---------------------------------------------------------
**----------------------------------------------------------------------------------------------------------------------
*/


void print_parse_obj(t_object *obj)
{
	int i = 1;

	dprintf(1, "OBJ\n\n");
	while (obj)
	{
		printf("obj %d\n{\n", i++);
		printf("\tpos = x:%f | y:%f | z:%f\n", obj->pos.x, obj->pos.y, obj->pos.z);
		printf("\trot = x:%f | y:%f | z:%f\n", obj->rot.x, obj->rot.y, obj->rot.z);
		printf("\tfile = [%s]\n", obj->file);
        printf("\ttype = %d\n", obj->type);
        printf("********************************************  POLY LIST ******************************************\n");
       print_parse1(obj->poly);
        printf("********************************************  END ************************************************\n");
		printf("}\n");
		obj = obj->next;
	}
}

void print_parse1(t_poly *poly)
{
	int i = 1;

	//dprintf(1, "COUOCU11\n");
    while (poly){
		printf("\tpoly %d\n\t{\n", i++);
		printf("\t\tnb ply = %d\n", poly->nbr_p);
		printf("\t\tdot = x:%f | y:%f | z:%f\n", poly->dot[0].x, poly->dot[0].y, poly->dot[0].z);
		printf("\t\tdot = x:%f | y:%f | z:%f\n", poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
		printf("\t\tdot = x:%f | y:%f | z:%f\n", poly->dot[2].x, poly->dot[2].y, poly->dot[2].z);
		printf("\n");
        printf("\t\tnormal = x:%f | y:%f | z:%f\n", poly->normale.x, poly->normale.y, poly->normale.z);
        printf("\n");
		printf("\t\tX = %f | Y = %f\n", poly->cord[0].x, poly->cord[0].y);
		printf("\t\tX = %f | Y = %f\n", poly->cord[1].x, poly->cord[1].y);
		printf("\t\tX = %f | Y = %f\n", poly->cord[2].x, poly->cord[2].y);
        printf("\t\tr = %hhu g = %hhu b = %hhu\n", poly->mtl.ka.r, poly->mtl.ka.g, poly->mtl.ka.b);
        printf("\t\tr = %hhu g = %hhu b = %hhu\n", poly->mtl.kd.r, poly->mtl.kd.g, poly->mtl.kd.b);
		printf("\t}\n");
        poly = poly->next;
    }
}


/*
**------------------------------------------------------POLY-------------------------------------------------------------
*/


void print_parse(t_poly *poly)
{
	int i = 1;

	//dprintf(1, "COUOCU11\n");
	while (poly)
	{
		printf("poly %d\n{\n", i++);
		printf("\tnb ply = %d\n", poly->nbr_p);
		printf("\tdot = x:%f | y:%f | z:%f\n", poly->dot[0].x, poly->dot[0].y, poly->dot[0].z);
		printf("\tdot = x:%f | y:%f | z:%f\n", poly->dot[1].x, poly->dot[1].y, poly->dot[1].z);
		printf("\tdot = x:%f | y:%f | z:%f\n", poly->dot[2].x, poly->dot[2].y, poly->dot[2].z);
		printf("\tdot = x:%f | y:%f | z:%f\n", poly->dot[3].x, poly->dot[3].y, poly->dot[3].z);
		printf("\n");
		printf("\tX = %f | Y = %f\n", poly->cord[0].x, poly->cord[0].y);
		printf("\tX = %f | Y = %f\n", poly->cord[1].x, poly->cord[1].y);
		printf("\tX = %f | Y = %f\n", poly->cord[2].x, poly->cord[2].y);
		printf("\tX = %f | Y = %f\n", poly->cord[3].x, poly->cord[3].y);
		printf("\ttextur = [%s]\n", poly->tex);
		printf("}\n");
		poly = poly->next;
	}
}

/*
**------------------------------------------------------TEX-------------------------------------------------------------
*/

int	keyboard_test(int key, t_input *inputs)
{
    if (key == 49)
    {
        mlx_clear_window(inputs->im.ad, inputs->win_ad);
        mlx_put_image_to_window(inputs->im.ad, inputs->win_ad, inputs->map->tex_tab.tab, 0, 0);
        dprintf(1, "%s\n", inputs->map->tex);
        if (inputs->map->next)
            inputs->map = inputs->map->next;
        else
             return 0;
    }
    if (key == 83)
    {
        if (!inputs->obj->poly->mtl.tex.tab)
        {
            dprintf(1, "nop\n");
            return 0;
        }
        mlx_clear_window(inputs->im.ad, inputs->win_ad);
        mlx_put_image_to_window(inputs->im.ad, inputs->win_ad, inputs->obj->poly->mtl.tex.tab, 0, 0);
        dprintf(1, "%s\n", "bla");
        if (inputs->obj->poly->next)
            inputs->obj->poly = inputs->obj->poly->next;
        else if (inputs->obj->next)
            inputs->obj = inputs->obj->next;
        else
             return 0;
    }
    return 0;
}

/*
**--------------------------------------------------END-----------------------------------------------------------------
**----------------------------------------------------------------------------------------------------------------------
*/

int main(int c, char **v)
{
    //sleep(10);
    (void)c;
    t_input data;
    //t_poly  *poly;

    //poly = (t_poly *)malloc(sizeof(t_poly));
    //data.nbrpoly = Debugfct(poly);


    // printf("init vars\n");
    init_var(&data);
    //data.map = parsing_poly(v[1], &data);
    if(!(data.map = parsing_poly(v[1], &data)))
    {
        printf("BLALALALALA\n");
        sleep(20);
    	return(0);
    }
  print_parse(data.map);
  print_parse_obj(data.obj);

// mlx_put_image_to_window(data.im.ad, data.win_ad, data.map->tex_tab.im.ad, 0, 0);
    mlx_hook(data.win_ad, 2, 0, keyboard_test, &data);
   // mlx_put_image_to_window(data.map->tex_tab.im.tab, data.win_ad, data.map->tex_tab.im.ad, 0, 0);
    

    // while (data.map)
    // {
    //     display_window(&data, data.map);
    //     data.map = data.map->next;
    // }


//     printf("ray init\n");
//     data.rays = tab_ray(data.win_h * data.win_w, &data);
//     printf("ray init end\n");
//     get_plans(data.map);
//     printf("plans init end\n");
//    /*thread_start(&data);*/
//     proj_2d(data.map, &data);
//     printf("proj2d end\n");
 //	mlx_put_image_to_window(data.im.tab, data.win_ad, data.im.ad, 0, 0);
 	//mlx_hook(data.win_ad, 2, 0, keyboard_move, &data);
// 	/*mlx_hook(inputs.win_ad, 17, 0, &ft_close, &inputs);*/
 	mlx_loop(data.mlx_ad);
    free_poly(&(data.map));
    return(0);
}
