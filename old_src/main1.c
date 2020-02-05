/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main1.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mwaterso <mwaterso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/10/22 17:37:46 by mwaterso     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/22 19:31:00 by mwaterso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "SDL_image.h"
#include "SDL.h"

int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
 
    SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE);
    
    while(1);
 
    SDL_Quit();
 
    return EXIT_SUCCESS;
}