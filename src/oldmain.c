/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/05 14:17:42 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2020/01/07 16:18:07 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../includes/doom.h" 

void visual(int i, t_input *data, double rotx, double rotz)
{
    double a;  
    double b;
    double dist;

}

t_ray *tab_ray(int nbrpix, t_input *data)
{
    t_ray *new;
    int i;

    i = 0;
    new = malloc(sizeof(t_ray) * nbrpix);
    while (i < data->win_h * data->win_w)
    {
        new[i].x = 1;
        new[i].y = (X_VIEW / 2 - ((data->win_w - i % data->win_w) / data->win_w) * X_VIEW);
        new[i].z = (Z_VIEW / 2 - ((data->win_h - i / data->win_h) / data->win_h) * Z_VIEW);
        i++;
    }
    return (new);
}

/*t_ray   process_ray(double  rotx, double rotz, t_fdot pos_player)
{
    return (ray);
}*/

t_dot define_way(t_fdot angle)
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
}


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

void raycast(t_thread* thread)
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
}

void thread_start(t_input	*data)
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
}

int main(int argc, char *argv[])
{
    t_input data;
    SDL_Event event;
    
    printf("main\n");
    data.win_h = 1000;
    data.win_w = 1000;
    data.alpha_x = 0;
    data.alpha_z = 0;
    if(0 != SDL_Init(SDL_INIT_VIDEO))
        printf("Erreur init\n");
    if (!(data.window = SDL_CreateWindow("title", 0, 0, data.win_w, data.win_h, 0)))
        printf("Erreur window\n");
    data.rays = tab_ray(data.win_h * data.win_w, &data);
    thread_start(&data);
    while (1)
    {
        SDL_PollEvent(&event);
    }

    SDL_DestroyWindow(data.window);
    SDL_Quit();
    return EXIT_SUCCESS;
}
