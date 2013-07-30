#include "../include/plant.h"

Plant::Plant(int x, int y)
:Object(x, y)
{
    // Online code for creating a new surface
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
    #else
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
    #endif

    surface = SDL_CreateRGBSurface(SDL_SWSURFACE, 6, 6, 32,
                                   rmask, gmask, bmask, amask);

    Uint32 *pixels = (Uint32 *)surface->pixels;
    for(int x=0; x<6; ++x)
    {
        for(int y=0; y<6; ++y)
        {
            pixels[ ( y * surface->w ) + x ] = SDL_MapRGB(surface->format, 0, 50, 0);
        }
    }
    setBody(surface);
}

Plant::~Plant()
{
    //dtor
}

void Plant::look(const SDL_Surface* world)
{

}

void Plant::collision(Object* obj)
{

}
